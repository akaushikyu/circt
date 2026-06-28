/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Calyx.td                                                             *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class AddFOpIEEE754;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class AddLibOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class AndLibOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Calyx Assignment
/// The "calyx.assign" operation represents a non-blocking
/// assignment. An assignment may optionally be guarded,
/// which controls when the assignment should be active.
/// This operation should only be instantiated in the
/// "calyx.wires" section or a "calyx.group".
/// 
/// ```mlir
///   calyx.assign %dest = %src : i16
///   calyx.assign %dest = %guard ? %src : i16
/// ```
class AssignOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Calyx Combinational Component
/// The "calyx.comb_component" operation represents a Calyx combinational component containing:
/// (1) In- and output port definitions that define the interface.
/// (2) Combinational cells and wires.
/// 
/// ```mlir
///   calyx.comb_component @C(%in: i32) -> (%out: i16) {
///     ...
///     calyx.wires { ... }
///   }
/// ```
class CombComponentOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Calyx Combinational Group
/// Represents a Calyx combinational group, which is a collection
/// of combinational assignments that are only active when the group
/// is run from the control execution schedule.
/// A combinational group does not have group_go or group_done operators.
/// 
/// ```mlir
///   calyx.comb_group @MyCombGroup {
///     calyx.assign %1 = %2 : i32
///   }
/// ```
class CombGroupOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class CompareFOpIEEE754;

} // namespace circt::calyx
namespace circt::calyx {

/// Calyx Component
/// The "calyx.component" operation represents an overall Calyx component containing:
/// (1) In- and output port definitions that define the interface.
/// (2) The cells, wires, and control schedule.
/// 
/// A Calyx component requires attributes `clk`, `go`, and `reset` on separate input ports,
/// and `done` on an output port.
/// 
/// ```mlir
///   calyx.component @C(%in: i32, %go: i1 {go}, %clk: i1 {clk}, %reset: i1 {reset}) -> (%out: i16, %done: i1 {done}) {
///     ...
///     calyx.wires { ... }
///     calyx.control { ... }
///   }
/// ```
class ComponentOp;

} // namespace circt::calyx
namespace circt::calyx {

/// constant capable of representing an integer or floating point value
/// The `constant` operation is a wrapper around bit vectors with fixed-size number of bits.
/// Specific value and intended type should be specified via attribute only.
/// 
/// Example:
/// 
/// ```
/// // Integer constant
/// %1 = calyx.constant <42 : i32> : i32
/// 
/// // Floating point constant
/// %1 = calyx.constant <4.2 : f32> : i32
/// ```
class ConstantOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Calyx Control
/// The "calyx.control" operation represents the
/// execution schedule defined for the given
/// component, i.e. when each group executes.
/// 
/// ```mlir
///   calyx.control {
///     calyx.seq {
///       calyx.enable @GroupA
///     }
///   }
/// ```
class ControlOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Calyx Static Cycle Op
/// Returns an I1 signal that is active `start` cycles after the static 
/// group starts, and inactive all other times. Optional `end` 
/// attribute allows the signal to be active from until `end` cycles
/// after the static group starts. Must be used within a static group.
/// 
/// ```mlir
///   calyx.static_group latency<2> @MyStaticGroup {
///     %1 = calyx.cycle 1 : i1
///   }
/// ```
class CycleOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class DivSPipeLibOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class DivSqrtOpIEEE754;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class DivUPipeLibOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Calyx Enable
/// The "calyx.enable" operation represents the execution of
/// a group defined explicitly in the "calyx.wires" section.
/// 
/// The 'compiledGroups' attribute is used in the Compile
/// Control pass to track which groups are compiled within
/// the new compilation group.
/// 
/// ```mlir
///   calyx.enable @SomeGroup
/// ```
class EnableOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class EqLibOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class ExtSILibOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class FpToIntOpIEEE754;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class GeLibOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Calyx Group Done Port
/// The "calyx.group_done" operation represents a port on a
/// Calyx group that signifies when the group is finished.
/// A done operation may optionally be guarded, which controls
/// when the group's done operation should be active.
/// 
/// ```mlir
///   calyx.group_done %src : i1
///   calyx.group_done %guard ? %src : i1
/// ```
class GroupDoneOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Calyx Group Go Port
/// The "calyx.group_go" operation represents a port on a
/// Calyx group that signifies when the group begins.
/// A go operation may optionally be guarded, which
/// controls when the group's go operation should be
/// active. The go operation should only be inserted
/// during the Go Insertion pass. It does not
/// receive a source until the Compile Control pass.
/// 
/// ```mlir
///   %group_name1.go = calyx.group_go %src : i1
///   %group_name2.go = calyx.group_go %guard ? %src : i1
/// ```
class GroupGoOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Calyx Group
/// Represents a Calyx group, which is a collection
/// of assignments that are only active when the group
/// is run from the control execution schedule. A group
/// signifies its termination with a special port named
/// a "done" port.
/// 
/// ```mlir
///   calyx.group @MyGroup {
///     calyx.assign %1 = %2 : i32
///     calyx.group_done %3 : i1
///   }
/// ```
class GroupOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class GtLibOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Calyx If
/// The "calyx.if" operation represents and if-then-else construct for
/// conditionally executing two Calyx groups. The operands to an if operation is
/// a 1-bit port and an optional combinational group under which this port is driven.
/// 
/// Note: The native and CIRCT Calyx IRs may diverge wrt. 'with' execution, see:
/// https://github.com/cucapra/calyx/discussions/588
/// 
/// ```mlir
///   calyx.if %1 with @G1 {
///     calyx.enable @G2
///     ...
///   } else {
///     calyx.enable @G3
///     ...
///   }
///   calyx.if %1 {
///     calyx.enable @G2
///     ...
///   }
/// ```
class IfOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Calyx Component Instance
/// Represents an instance of a Calyx component, which may include state.
/// 
/// ```mlir
///   %c.in, %c.out = calyx.instance @c of @MyComponent : i64, i16
/// ```
class InstanceOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class IntToFpOpIEEE754;

} // namespace circt::calyx
namespace circt::calyx {

/// Calyx Invoke
/// calyx.invoke is similar to the behavior of a function 
/// call, which invokes a given component.
/// 
/// The 'callee' attribute is the name of the component,
/// the 'ports' attribute specifies the input port of the component when it is invoked,
/// the 'inputs' attribute specifies the assignment on the corresponding port,
/// and the 'refCellsMap' attribute maps the reference cells in the `callee` with
/// the original cells in the caller.
/// 
/// ```mlir
///   calyx.component @identity {
///     %mem.addr0, %mem.clk, ... = calyx.seq_mem @mem <[1] x 32> [1] {external = false}
///   }
///   %id.in, %id.out, ... = calyx.instance @id of @identity : i32, i32, ...
///   %r.in, ... = calyx.register @r : i32, ...
///   %mem_1.addr0, %mem_1.clk, ... = calyx.seq_mem @mem_1 <[1] x 32> [1] {external = true}
///   ...
///   calyx.control {
///     calyx.seq {
///       calyx.invoke @id[mem = mem_1](%id.in = %c1_10, %r.in = %id.out) -> (i32, i32)
///     }
///   }
/// ```
class InvokeOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class LeLibOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class LshLibOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class LtLibOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines a memory
/// The "calyx.memory" op defines a memory. Memories can have any number of
/// dimensions, as specified by the length of the `$sizes` and `$addrSizes`
/// arrays. The `$addrSizes` specify the bitwidth of each dimension's address,
/// and should be wide enough to address the range of the corresponding
/// dimension in `$sizes`. The `$width` attribute dictates the width of a single
/// element.
/// 
/// See https://docs.calyxir.org/libraries/core.html#memories for
/// more information.
/// 
/// ```mlir
///   // A 1-dimensional, 32-bit memory with size dimension 1. Equivalent representation in the native compiler:
///   // `m1 = std_mem_d1(32, 1, 1)`
///   %m1.addr0, %m1.write_data, %m1.write_en, %m1.clk, %m1.read_data, %m1.done = calyx.memory @m1 <[1] x 32> [1] : i1, i32, i1, i1, i32, i1
/// 
///   // A 2-dimensional, 8-bit memory with size dimensions 64 x 64. Equivalent representation in the native compiler:
///   // `m2 = std_mem_d2(8, 64, 64, 6, 6)`
///   %m2.addr0, %m2.addr1, %m2.write_data, %m2.write_en, %m2.clk, %m2.read_data, %m2.done = calyx.memory @m2 <[64, 64] x 8> [6, 6] : i6, i6, i8, i1, i1, i8, i1
/// ```
class MemoryOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class MulFOpIEEE754;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class MultPipeLibOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class MuxLibOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class NeqLibOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class NotLibOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class OrLibOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class PadLibOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Calyx Parallel
/// The "calyx.par" operation executes the
/// control within its region in parallel.
/// 
/// ```mlir
///   calyx.par {
///     // G1 and G2 will execute in parallel.
///     // The region is complete when both
///     // G1 and G2 are done.
///     calyx.enable @G1
///     calyx.enable @G2
///   }
/// ```
class ParOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Calyx Primitive Instance
/// Represents an instance of a Calyx primitive.
/// 
/// ```mlir
///   %c.in, %c.out = calyx.primitive @c of @MyExternalPrimitive : i64, i16
/// ```
class PrimitiveOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines a register
/// The "calyx.register" op defines a register.
/// ```mlir
///   // A 32-bit register.
///   %r.in, %r.write_en, %r.clk, %r.reset, %r.out, %r.done = calyx.register @r : i32, i1, i1, i1, i32, i1
/// ```
class RegisterOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class RemSPipeLibOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class RemUPipeLibOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Calyx Dynamic Repeat
/// The "calyx.repeat" operation represents the repeated execution of
/// the control within its region.
/// The key difference with static repeat is that the body (unlike with static 
/// repeat) can be dynamically timed. 
/// 
/// ```mlir
///   calyx.repeat 10 {
///     calyx.enable @G1
///     ...
///   }
/// ```
class RepeatOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class RshLibOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class SeqLibOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines a memory with sequential read
/// The "calyx.seq_mem" op defines a memory with sequential reads. Memories can
/// have any number of dimensions, as specified by the length of the `$sizes` and
/// `$addrSizes` arrays. The `$addrSizes` specify the bitwidth of each dimension's
/// address, and should be wide enough to address the range of the corresponding
/// dimension in `$sizes`. The `$width` attribute dictates the width of a single
/// element.
/// 
/// See https://docs.calyxir.org/libraries/core.html#memories for
/// more information.
/// 
/// ```mlir
///   // A 1-dimensional, 32-bit memory with size dimension 1. Equivalent representation in the native compiler:
///   // `m1 = seq_mem_d1(32, 1, 1)`
///   %m1.addr0, %m1.write_data, %m1.write_en, %m1.clk, %m1.read_data, %m1.read_en, %m1.done = calyx.memory @m1 <[1] x 32> [1] : i1, i32, i1, i1, i32, i1
/// 
///   // A 2-dimensional, 8-bit memory with size dimensions 64 x 64. Equivalent representation in the native compiler:
///   // `m2 = seq_mem_d2(8, 64, 64, 6, 6)`
///   %m2.addr0, %m2.addr1, %m2.write_data, %m2.write_en, %m2.write_done, %m2.clk, %m2.read_data, %m2.read_en, %m2.read_done = calyx.memory @m2 <[64, 64] x 8> [6, 6] : i6, i6, i8, i1, i1, i8, i1
/// ```
class SeqMemoryOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Calyx Sequential
/// The "calyx.seq" operation executes the
/// control within its region sequentially.
/// 
/// ```mlir
///   calyx.seq {
///     // G2 will not begin execution until G1 is done.
///     calyx.enable @G1
///     calyx.enable @G2
///   }
/// ```
class SeqOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class SgeLibOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class SgtLibOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class ShruLibOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class SleLibOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class SliceLibOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class SltLibOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class SneqLibOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class SrshLibOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Calyx Static Group
/// Represents a Calyx static group, which is a collection
/// of assignments that are only active when the group
/// is run from the control execution schedule. A group
/// signifies its termination with a special port named
/// a "done" port.
/// 
/// ```mlir
///   calyx.static_group latency<1> @MyStaticGroup {
///     calyx.assign %1 = %2 : i32
///   }
/// ```
class StaticGroupOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Calyx Static If
/// The "calyx.static_if" operation represents an if-then-else construct for
/// conditionally executing two Calyx groups. The operands to an if operation is
/// a 1-bit port. 
/// 
/// ```mlir
///   calyx.static_if %1 {
///     calyx.enable @G2
///     ...
///   } else {
///     calyx.enable @G3
///     ...
///   }
///   calyx.if %1 {
///     calyx.enable @G2
///     ...
///   }
/// ```
class StaticIfOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Calyx Static Parallel
/// The "calyx.static_par" operation executes the
/// control within its region in parallel.
/// 
/// ```mlir
///   calyx.static_par {
///     // G1 and G2 will execute in parallel.
///     // The region is complete when both
///     // G1 and G2 are done.
///     calyx.enable @G1
///     calyx.enable @G2
///   }
/// ```
class StaticParOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Calyx Static Repeat
/// The "calyx.static_repeat" operation represents the repeated execution of
/// the control within its region. All control within the region must be static.
/// 
/// ```mlir
///   calyx.static_repeat 10 {
///     calyx.enable @G1
///     ...
///   }
/// ```
class StaticRepeatOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Calyx Static Seq
/// The "calyx.static_seq" operation executes the
/// control within its region sequentially.
/// 
/// ```mlir
///   calyx.static_seq {
///     // G2 will not begin execution until G1 is done.
///     calyx.enable @G1
///     calyx.enable @G2
///   }
/// ```
class StaticSeqOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class SubLibOp;

} // namespace circt::calyx
namespace circt::calyx {

/// An undefined signal
/// The "calyx.undef" op defines an undefined signal. An undefined signal can be
/// replaced with any value representable in n-bits.
/// ```mlir
///   // A 32-bit undefined value
///   %undef.out = calyx.undef @undef : i32
/// ```
class UndefLibOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Calyx Undefined Value
/// The "undef" operation represents an undefined value
/// that may be used when a specific source or destination
/// does not have an assignment yet. This is used to avoid
/// pulling in the entire LLVMIR dialect for a single
/// operation.
/// 
/// ```mlir
///   %0 = calyx.undef : i1
/// ```
class UndefinedOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Calyx While
/// The "calyx.while" operation represents a construct for continuously
/// executing the inner groups of the 'while' operation while the condition port
/// evaluates to true. The operands to a while operation is a 1-bit port and an
/// optional combinational group under which this port is driven.
/// 
/// Note: The native and CIRCT Calyx IRs may diverge wrt. 'with' execution, see:
/// https://github.com/cucapra/calyx/discussions/588
/// 
/// ```mlir
///   calyx.while %1 with @G1 {
///     calyx.enable @G2
///     ...
///   }
///   calyx.while %1 {
///     calyx.enable @G2
///     ...
///   }
/// ```
class WhileOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class WireLibOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Calyx Wires
/// The "calyx.wires" operation represents a set of
/// guarded connections between component instances,
/// which may be placed within groups.
/// 
/// ```mlir
///   calyx.wires {
///     calyx.group @A { ... }
///     calyx.assign %1 = %2 : i16
///   }
/// ```
class WiresOp;

} // namespace circt::calyx
namespace circt::calyx {

/// Defines an operation which maps to a Calyx library primitive
/// This operation represents an instance of a Calyx library primitive.
/// A library primitive maps to some hardware-implemented component within the
/// native Calyx compiler.
/// 
/// ```mlir
///   // A 32-bit adder. This falls under the binary library operations.
///   %add.left, %add.right, %add.out = calyx.std_add @add : i32, i32, i32
/// 
///   // An 8-bit comparison operator (with a 1-bit output). This falls under
///   // the boolean binary library operations.
///   %gt.left, %gt.right, %gt.out = calyx.std_gt @gt : i8, i8, i1
/// 
///   // An 8-bit to 16-bit pad operator. This falls under the unary
///   // library operations.
///   %pad.in, %pad.out = calyx.std_pad @pad : i8, i16
/// ```
class XorLibOp;

} // namespace circt::calyx
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::AddFOpIEEE754 declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AddFOpIEEE754GenericAdaptorBase {
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
  AddFOpIEEE754GenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.ieee754.add", odsAttrs.getContext());
  }

  AddFOpIEEE754GenericAdaptorBase(AddFOpIEEE754 op);

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
class AddFOpIEEE754GenericAdaptor : public detail::AddFOpIEEE754GenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AddFOpIEEE754GenericAdaptorBase;
public:
  AddFOpIEEE754GenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AddFOpIEEE754GenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : AddFOpIEEE754GenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AddFOpIEEE754GenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AddFOpIEEE754GenericAdaptor(values, attrs, Properties{}, {}) {}

  AddFOpIEEE754GenericAdaptor(RangeT values, const AddFOpIEEE754GenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AddFOpIEEE754, typename = std::enable_if_t<std::is_same_v<LateInst, AddFOpIEEE754>>>
  AddFOpIEEE754GenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class AddFOpIEEE754Adaptor : public AddFOpIEEE754GenericAdaptor<::mlir::ValueRange> {
public:
  using AddFOpIEEE754GenericAdaptor::AddFOpIEEE754GenericAdaptor;
  AddFOpIEEE754Adaptor(AddFOpIEEE754 op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AddFOpIEEE754 : public ::mlir::Op<AddFOpIEEE754, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<11>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::FloatingPointOpInterface::Trait, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AddFOpIEEE754Adaptor;
  template <typename RangeT>
  using GenericAdaptor = AddFOpIEEE754GenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<AddFOpIEEE754>::instanceName;
  using ::circt::calyx::CellInterface::Trait<AddFOpIEEE754>::portIndex;
  using ::circt::calyx::CellInterface::Trait<AddFOpIEEE754>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<AddFOpIEEE754>::portInfo;
  using ::circt::calyx::CellInterface::Trait<AddFOpIEEE754>::direction;
  using ::circt::calyx::CellInterface::Trait<AddFOpIEEE754>::portName;
  using ::circt::calyx::CellInterface::Trait<AddFOpIEEE754>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<AddFOpIEEE754>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<AddFOpIEEE754>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<AddFOpIEEE754>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<AddFOpIEEE754>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<AddFOpIEEE754>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<AddFOpIEEE754>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.ieee754.add");
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

  ::mlir::TypedValue<::mlir::IntegerType> getClk() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getReset() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getGo() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(2).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getControl() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(3).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getSubOp() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(4).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getLeft() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(5).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getRight() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(6).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getRoundingMode() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(7).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(8).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getExceptionalFlags() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(9).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getDone() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(10).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static AddFOpIEEE754 create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static AddFOpIEEE754 create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static FloatingPointStandard getFloatingPointStandard();
  static std::string getCalyxLibraryName();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::AddFOpIEEE754)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::AddFOpIEEE754GenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::AddLibOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AddLibOpGenericAdaptorBase {
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
  AddLibOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.std_add", odsAttrs.getContext());
  }

  AddLibOpGenericAdaptorBase(AddLibOp op);

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
class AddLibOpGenericAdaptor : public detail::AddLibOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AddLibOpGenericAdaptorBase;
public:
  AddLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AddLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : AddLibOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AddLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AddLibOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AddLibOpGenericAdaptor(RangeT values, const AddLibOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AddLibOp, typename = std::enable_if_t<std::is_same_v<LateInst, AddLibOp>>>
  AddLibOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class AddLibOpAdaptor : public AddLibOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AddLibOpGenericAdaptor::AddLibOpGenericAdaptor;
  AddLibOpAdaptor(AddLibOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AddLibOp : public ::mlir::Op<AddLibOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<3>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::Combinational, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AddLibOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AddLibOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<AddLibOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<AddLibOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<AddLibOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<AddLibOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<AddLibOp>::direction;
  using ::circt::calyx::CellInterface::Trait<AddLibOp>::portName;
  using ::circt::calyx::CellInterface::Trait<AddLibOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<AddLibOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<AddLibOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<AddLibOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<AddLibOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<AddLibOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<AddLibOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.std_add");
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

  ::mlir::TypedValue<::mlir::Type> getLeft() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getRight() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(2).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static AddLibOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static AddLibOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::AddLibOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::AddLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::AndLibOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AndLibOpGenericAdaptorBase {
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
  AndLibOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.std_and", odsAttrs.getContext());
  }

  AndLibOpGenericAdaptorBase(AndLibOp op);

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
class AndLibOpGenericAdaptor : public detail::AndLibOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AndLibOpGenericAdaptorBase;
public:
  AndLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AndLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : AndLibOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AndLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AndLibOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AndLibOpGenericAdaptor(RangeT values, const AndLibOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AndLibOp, typename = std::enable_if_t<std::is_same_v<LateInst, AndLibOp>>>
  AndLibOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class AndLibOpAdaptor : public AndLibOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AndLibOpGenericAdaptor::AndLibOpGenericAdaptor;
  AndLibOpAdaptor(AndLibOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AndLibOp : public ::mlir::Op<AndLibOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<3>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::Combinational, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AndLibOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AndLibOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<AndLibOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<AndLibOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<AndLibOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<AndLibOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<AndLibOp>::direction;
  using ::circt::calyx::CellInterface::Trait<AndLibOp>::portName;
  using ::circt::calyx::CellInterface::Trait<AndLibOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<AndLibOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<AndLibOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<AndLibOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<AndLibOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<AndLibOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<AndLibOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.std_and");
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

  ::mlir::TypedValue<::mlir::Type> getLeft() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getRight() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(2).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static AndLibOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static AndLibOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::AndLibOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::AndLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::AssignOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AssignOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  AssignOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.assign", odsAttrs.getContext());
  }

  AssignOpGenericAdaptorBase(AssignOp op);

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
class AssignOpGenericAdaptor : public detail::AssignOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AssignOpGenericAdaptorBase;
  static constexpr int odsIndex_dest = 0;
  static constexpr int odsIndex_src = 1;
  static constexpr int odsIndex_guard = 2;
public:
  AssignOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AssignOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : AssignOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AssignOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AssignOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AssignOpGenericAdaptor(RangeT values, const AssignOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AssignOp, typename = std::enable_if_t<std::is_same_v<LateInst, AssignOp>>>
  AssignOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getDest() {
    return (*getODSOperands(0).begin());
  }

  ValueT getSrc() {
    return (*getODSOperands(1).begin());
  }

  ValueT getGuard() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AssignOpAdaptor : public AssignOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AssignOpGenericAdaptor::AssignOpGenericAdaptor;
  AssignOpAdaptor(AssignOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AssignOp : public ::mlir::Op<AssignOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::HasParent<GroupOp, CombGroupOp, StaticGroupOp, WiresOp>::Impl, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AssignOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AssignOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_dest = 0;
  static constexpr int odsIndex_src = 1;
  static constexpr int odsIndex_guard = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("calyx.assign");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getDest() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getSrc() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getGuard() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::OpOperand &getDestMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getSrcMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getGuardMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value dest, Value src);
  static AssignOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value dest, Value src);
  static AssignOp create(::mlir::ImplicitLocOpBuilder &builder, Value dest, Value src);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value dest, ::mlir::Value src, /*optional*/::mlir::Value guard);
  static AssignOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value dest, ::mlir::Value src, /*optional*/::mlir::Value guard);
  static AssignOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value dest, ::mlir::Value src, /*optional*/::mlir::Value guard);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value dest, ::mlir::Value src, /*optional*/::mlir::Value guard);
  static AssignOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value dest, ::mlir::Value src, /*optional*/::mlir::Value guard);
  static AssignOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value dest, ::mlir::Value src, /*optional*/::mlir::Value guard);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AssignOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AssignOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AssignOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AssignOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
public:
};

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::AssignOp)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::CombComponentOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CombComponentOpGenericAdaptorBase {
public:
  struct Properties {
    using arg_attrsTy = ::mlir::ArrayAttr;
    arg_attrsTy arg_attrs;

    auto getArgAttrs() const {
      auto &propStorage = this->arg_attrs;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setArgAttrs(const ::mlir::ArrayAttr &propValue) {
      this->arg_attrs = propValue;
    }
    using function_typeTy = ::mlir::TypeAttr;
    function_typeTy function_type;

    auto getFunctionType() const {
      auto &propStorage = this->function_type;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setFunctionType(const ::mlir::TypeAttr &propValue) {
      this->function_type = propValue;
    }
    using portAttributesTy = ::mlir::ArrayAttr;
    portAttributesTy portAttributes;

    auto getPortAttributes() const {
      auto &propStorage = this->portAttributes;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setPortAttributes(const ::mlir::ArrayAttr &propValue) {
      this->portAttributes = propValue;
    }
    using portDirectionsTy = ::mlir::IntegerAttr;
    portDirectionsTy portDirections;

    auto getPortDirections() const {
      auto &propStorage = this->portDirections;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setPortDirections(const ::mlir::IntegerAttr &propValue) {
      this->portDirections = propValue;
    }
    using portNamesTy = ::mlir::ArrayAttr;
    portNamesTy portNames;

    auto getPortNames() const {
      auto &propStorage = this->portNames;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setPortNames(const ::mlir::ArrayAttr &propValue) {
      this->portNames = propValue;
    }
    using res_attrsTy = ::mlir::ArrayAttr;
    res_attrsTy res_attrs;

    auto getResAttrs() const {
      auto &propStorage = this->res_attrs;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setResAttrs(const ::mlir::ArrayAttr &propValue) {
      this->res_attrs = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.arg_attrs == this->arg_attrs &&
        rhs.function_type == this->function_type &&
        rhs.portAttributes == this->portAttributes &&
        rhs.portDirections == this->portDirections &&
        rhs.portNames == this->portNames &&
        rhs.res_attrs == this->res_attrs &&
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
  CombComponentOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.comb_component", odsAttrs.getContext());
  }

  CombComponentOpGenericAdaptorBase(CombComponentOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::TypeAttr getFunctionTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().function_type);
    return attr;
  }

  ::mlir::FunctionType getFunctionType();
  ::mlir::ArrayAttr getArgAttrsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().arg_attrs);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getArgAttrs();
  ::mlir::ArrayAttr getResAttrsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().res_attrs);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getResAttrs();
  ::mlir::ArrayAttr getPortNamesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().portNames);
    return attr;
  }

  ::mlir::ArrayAttr getPortNames();
  ::mlir::ArrayAttr getPortAttributesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().portAttributes);
    return attr;
  }

  ::mlir::ArrayAttr getPortAttributes();
  ::mlir::IntegerAttr getPortDirectionsAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().portDirections);
    return attr;
  }

  ::mlir::APInt getPortDirections();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class CombComponentOpGenericAdaptor : public detail::CombComponentOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CombComponentOpGenericAdaptorBase;
public:
  CombComponentOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CombComponentOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : CombComponentOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CombComponentOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CombComponentOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CombComponentOpGenericAdaptor(RangeT values, const CombComponentOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CombComponentOp, typename = std::enable_if_t<std::is_same_v<LateInst, CombComponentOp>>>
  CombComponentOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class CombComponentOpAdaptor : public CombComponentOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CombComponentOpGenericAdaptor::CombComponentOpGenericAdaptor;
  CombComponentOpAdaptor(CombComponentOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CombComponentOp : public ::mlir::Op<CombComponentOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<mlir::ModuleOp>::Impl, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::SymbolTable, ::mlir::SymbolOpInterface::Trait, ::mlir::ArgAndResultAttrsOpInterface::Trait, ::mlir::CallableOpInterface::Trait, ::mlir::FunctionOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::OpAsmOpInterface::Trait, ::circt::calyx::ComponentInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CombComponentOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CombComponentOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("arg_attrs"), ::llvm::StringRef("function_type"), ::llvm::StringRef("portAttributes"), ::llvm::StringRef("portDirections"), ::llvm::StringRef("portNames"), ::llvm::StringRef("res_attrs")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getArgAttrsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getArgAttrsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getFunctionTypeAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getFunctionTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getPortAttributesAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getPortAttributesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getPortDirectionsAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getPortDirectionsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getPortNamesAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getPortNamesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  ::mlir::StringAttr getResAttrsAttrName() {
    return getAttributeNameForIndex(5);
  }

  static ::mlir::StringAttr getResAttrsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 5);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("calyx.comb_component");
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
  ::mlir::TypeAttr getFunctionTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().function_type);
  }

  ::mlir::FunctionType getFunctionType();
  ::mlir::ArrayAttr getArgAttrsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().arg_attrs);
  }

  ::std::optional< ::mlir::ArrayAttr > getArgAttrs();
  ::mlir::ArrayAttr getResAttrsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().res_attrs);
  }

  ::std::optional< ::mlir::ArrayAttr > getResAttrs();
  ::mlir::ArrayAttr getPortNamesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().portNames);
  }

  ::mlir::ArrayAttr getPortNames();
  ::mlir::ArrayAttr getPortAttributesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().portAttributes);
  }

  ::mlir::ArrayAttr getPortAttributes();
  ::mlir::IntegerAttr getPortDirectionsAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().portDirections);
  }

  ::mlir::APInt getPortDirections();
  void setFunctionTypeAttr(::mlir::TypeAttr attr) {
    getProperties().function_type = attr;
  }

  void setFunctionType(::mlir::FunctionType attrValue);
  void setArgAttrsAttr(::mlir::ArrayAttr attr) {
    getProperties().arg_attrs = attr;
  }

  void setResAttrsAttr(::mlir::ArrayAttr attr) {
    getProperties().res_attrs = attr;
  }

  void setPortNamesAttr(::mlir::ArrayAttr attr) {
    getProperties().portNames = attr;
  }

  void setPortAttributesAttr(::mlir::ArrayAttr attr) {
    getProperties().portAttributes = attr;
  }

  void setPortDirectionsAttr(::mlir::IntegerAttr attr) {
    getProperties().portDirections = attr;
  }

  ::mlir::Attribute removeArgAttrsAttr() {
      auto attr = getProperties().arg_attrs;
      getProperties().arg_attrs = {};
      return attr;
  }

  ::mlir::Attribute removeResAttrsAttr() {
      auto attr = getProperties().res_attrs;
      getProperties().res_attrs = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringAttr name, ArrayRef<PortInfo> ports);
  static CombComponentOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr name, ArrayRef<PortInfo> ports);
  static CombComponentOp create(::mlir::ImplicitLocOpBuilder &builder, StringAttr name, ArrayRef<PortInfo> ports);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections);
  static CombComponentOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections);
  static CombComponentOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections);
  static CombComponentOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections);
  static CombComponentOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections);
  static CombComponentOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections);
  static CombComponentOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections);
  static CombComponentOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections);
  static CombComponentOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CombComponentOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CombComponentOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CombComponentOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CombComponentOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  SmallVector<circt::calyx::PortInfo> getPortInfo();
  SmallVector<circt::calyx::PortInfo> getInputPortInfo();
  SmallVector<circt::calyx::PortInfo> getOutputPortInfo();
  StringRef getName();
  bool isComb();
  Region*getRegion();
  Block*getBodyBlock();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
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
  using mlir::detail::FunctionOpInterfaceTrait<CombComponentOp>::front;
  using mlir::detail::FunctionOpInterfaceTrait<CombComponentOp>::getFunctionBody;

  /// Returns the argument types of this function.
  ArrayRef<Type> getArgumentTypes() { return getFunctionType().getInputs(); }

  /// Returns the result types of this function.
  ArrayRef<Type> getResultTypes() { return getFunctionType().getResults(); }

  /// Returns the region on the current operation that is callable.
  ::mlir::Region *getCallableRegion() {
    return &getBody();
  }

  /// Verify the type attribute of this function. Returns failure and emits
  /// an error if the attribute is invalid.
  LogicalResult verifyType() {
    auto type = getFunctionTypeAttr().getValue();
    if (!llvm::isa<FunctionType>(type))
      return emitOpError("requires '" +
                  getFunctionTypeAttrName().getValue() +
                         "' attribute of function type");
    return success();
  }

  /// Returns the WiresOp of a Calyx Component.
  WiresOp getWiresOp();

  void getAsmBlockArgumentNames(mlir::Region &region,
                                mlir::OpAsmSetValueNameFn setNameFn);
};

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::CombComponentOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::CombComponentOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::CombGroupOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CombGroupOpGenericAdaptorBase {
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
  CombGroupOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.comb_group", odsAttrs.getContext());
  }

  CombGroupOpGenericAdaptorBase(CombGroupOp op);

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
class CombGroupOpGenericAdaptor : public detail::CombGroupOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CombGroupOpGenericAdaptorBase;
public:
  CombGroupOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CombGroupOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : CombGroupOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CombGroupOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CombGroupOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CombGroupOpGenericAdaptor(RangeT values, const CombGroupOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CombGroupOp, typename = std::enable_if_t<std::is_same_v<LateInst, CombGroupOp>>>
  CombGroupOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class CombGroupOpAdaptor : public CombGroupOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CombGroupOpGenericAdaptor::CombGroupOpGenericAdaptor;
  CombGroupOpAdaptor(CombGroupOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CombGroupOp : public ::mlir::Op<CombGroupOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<WiresOp>::Impl, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::GroupInterface::Trait, ::mlir::RegionKindInterface::Trait, ::mlir::SymbolOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CombGroupOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CombGroupOpGenericAdaptor<RangeT>;
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
    return ::llvm::StringLiteral("calyx.comb_group");
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name);
  static CombGroupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name);
  static CombGroupOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringAttr sym_name);
  static CombGroupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr sym_name);
  static CombGroupOp create(::mlir::ImplicitLocOpBuilder &builder, StringAttr sym_name);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  LogicalResult drivesPort(Value port);
  LogicalResult drivesAllPorts(ValueRange ports);
  LogicalResult drivesAnyPort(ValueRange ports);
  LogicalResult readsAnyPort(ValueRange ports);
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
  static RegionKind getRegionKind(unsigned index) { return RegionKind::Graph; }

  /// Returns the body of a Calyx component.
  Block *getBodyBlock() {
    Region* region = &getOperation()->getRegion(0);
    assert(region->hasOneBlock() && "The body should have one Block.");
    return &region->front();
  }
};

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::CombGroupOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::CombGroupOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::CompareFOpIEEE754 declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CompareFOpIEEE754GenericAdaptorBase {
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
  CompareFOpIEEE754GenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.ieee754.compare", odsAttrs.getContext());
  }

  CompareFOpIEEE754GenericAdaptorBase(CompareFOpIEEE754 op);

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
class CompareFOpIEEE754GenericAdaptor : public detail::CompareFOpIEEE754GenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CompareFOpIEEE754GenericAdaptorBase;
public:
  CompareFOpIEEE754GenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CompareFOpIEEE754GenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : CompareFOpIEEE754GenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CompareFOpIEEE754GenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CompareFOpIEEE754GenericAdaptor(values, attrs, Properties{}, {}) {}

  CompareFOpIEEE754GenericAdaptor(RangeT values, const CompareFOpIEEE754GenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CompareFOpIEEE754, typename = std::enable_if_t<std::is_same_v<LateInst, CompareFOpIEEE754>>>
  CompareFOpIEEE754GenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class CompareFOpIEEE754Adaptor : public CompareFOpIEEE754GenericAdaptor<::mlir::ValueRange> {
public:
  using CompareFOpIEEE754GenericAdaptor::CompareFOpIEEE754GenericAdaptor;
  CompareFOpIEEE754Adaptor(CompareFOpIEEE754 op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CompareFOpIEEE754 : public ::mlir::Op<CompareFOpIEEE754, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<12>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::FloatingPointOpInterface::Trait, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CompareFOpIEEE754Adaptor;
  template <typename RangeT>
  using GenericAdaptor = CompareFOpIEEE754GenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<CompareFOpIEEE754>::instanceName;
  using ::circt::calyx::CellInterface::Trait<CompareFOpIEEE754>::portIndex;
  using ::circt::calyx::CellInterface::Trait<CompareFOpIEEE754>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<CompareFOpIEEE754>::portInfo;
  using ::circt::calyx::CellInterface::Trait<CompareFOpIEEE754>::direction;
  using ::circt::calyx::CellInterface::Trait<CompareFOpIEEE754>::portName;
  using ::circt::calyx::CellInterface::Trait<CompareFOpIEEE754>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<CompareFOpIEEE754>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<CompareFOpIEEE754>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<CompareFOpIEEE754>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<CompareFOpIEEE754>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<CompareFOpIEEE754>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<CompareFOpIEEE754>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.ieee754.compare");
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

  ::mlir::TypedValue<::mlir::IntegerType> getClk() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getReset() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getGo() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(2).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getLeft() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(3).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getRight() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(4).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getSignaling() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(5).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getLt() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(6).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getEq() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(7).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getGt() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(8).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getUnordered() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(9).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getExceptionalFlags() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(10).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getDone() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(11).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static CompareFOpIEEE754 create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static CompareFOpIEEE754 create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static FloatingPointStandard getFloatingPointStandard();
  static std::string getCalyxLibraryName();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::CompareFOpIEEE754)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::CompareFOpIEEE754GenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::ComponentOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ComponentOpGenericAdaptorBase {
public:
  struct Properties {
    using arg_attrsTy = ::mlir::ArrayAttr;
    arg_attrsTy arg_attrs;

    auto getArgAttrs() const {
      auto &propStorage = this->arg_attrs;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setArgAttrs(const ::mlir::ArrayAttr &propValue) {
      this->arg_attrs = propValue;
    }
    using function_typeTy = ::mlir::TypeAttr;
    function_typeTy function_type;

    auto getFunctionType() const {
      auto &propStorage = this->function_type;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setFunctionType(const ::mlir::TypeAttr &propValue) {
      this->function_type = propValue;
    }
    using portAttributesTy = ::mlir::ArrayAttr;
    portAttributesTy portAttributes;

    auto getPortAttributes() const {
      auto &propStorage = this->portAttributes;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setPortAttributes(const ::mlir::ArrayAttr &propValue) {
      this->portAttributes = propValue;
    }
    using portDirectionsTy = ::mlir::IntegerAttr;
    portDirectionsTy portDirections;

    auto getPortDirections() const {
      auto &propStorage = this->portDirections;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setPortDirections(const ::mlir::IntegerAttr &propValue) {
      this->portDirections = propValue;
    }
    using portNamesTy = ::mlir::ArrayAttr;
    portNamesTy portNames;

    auto getPortNames() const {
      auto &propStorage = this->portNames;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setPortNames(const ::mlir::ArrayAttr &propValue) {
      this->portNames = propValue;
    }
    using res_attrsTy = ::mlir::ArrayAttr;
    res_attrsTy res_attrs;

    auto getResAttrs() const {
      auto &propStorage = this->res_attrs;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setResAttrs(const ::mlir::ArrayAttr &propValue) {
      this->res_attrs = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.arg_attrs == this->arg_attrs &&
        rhs.function_type == this->function_type &&
        rhs.portAttributes == this->portAttributes &&
        rhs.portDirections == this->portDirections &&
        rhs.portNames == this->portNames &&
        rhs.res_attrs == this->res_attrs &&
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
  ComponentOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.component", odsAttrs.getContext());
  }

  ComponentOpGenericAdaptorBase(ComponentOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::TypeAttr getFunctionTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().function_type);
    return attr;
  }

  ::mlir::FunctionType getFunctionType();
  ::mlir::ArrayAttr getArgAttrsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().arg_attrs);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getArgAttrs();
  ::mlir::ArrayAttr getResAttrsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().res_attrs);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getResAttrs();
  ::mlir::ArrayAttr getPortNamesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().portNames);
    return attr;
  }

  ::mlir::ArrayAttr getPortNames();
  ::mlir::ArrayAttr getPortAttributesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().portAttributes);
    return attr;
  }

  ::mlir::ArrayAttr getPortAttributes();
  ::mlir::IntegerAttr getPortDirectionsAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().portDirections);
    return attr;
  }

  ::mlir::APInt getPortDirections();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class ComponentOpGenericAdaptor : public detail::ComponentOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ComponentOpGenericAdaptorBase;
public:
  ComponentOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ComponentOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ComponentOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ComponentOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ComponentOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ComponentOpGenericAdaptor(RangeT values, const ComponentOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ComponentOp, typename = std::enable_if_t<std::is_same_v<LateInst, ComponentOp>>>
  ComponentOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ComponentOpAdaptor : public ComponentOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ComponentOpGenericAdaptor::ComponentOpGenericAdaptor;
  ComponentOpAdaptor(ComponentOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ComponentOp : public ::mlir::Op<ComponentOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<mlir::ModuleOp>::Impl, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::RegionKindInterface::Trait, ::mlir::OpTrait::SymbolTable, ::mlir::SymbolOpInterface::Trait, ::mlir::ArgAndResultAttrsOpInterface::Trait, ::mlir::CallableOpInterface::Trait, ::mlir::FunctionOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::OpAsmOpInterface::Trait, ::circt::calyx::ComponentInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ComponentOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ComponentOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("arg_attrs"), ::llvm::StringRef("function_type"), ::llvm::StringRef("portAttributes"), ::llvm::StringRef("portDirections"), ::llvm::StringRef("portNames"), ::llvm::StringRef("res_attrs")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getArgAttrsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getArgAttrsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getFunctionTypeAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getFunctionTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getPortAttributesAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getPortAttributesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getPortDirectionsAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getPortDirectionsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getPortNamesAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getPortNamesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  ::mlir::StringAttr getResAttrsAttrName() {
    return getAttributeNameForIndex(5);
  }

  static ::mlir::StringAttr getResAttrsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 5);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("calyx.component");
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
  ::mlir::TypeAttr getFunctionTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().function_type);
  }

  ::mlir::FunctionType getFunctionType();
  ::mlir::ArrayAttr getArgAttrsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().arg_attrs);
  }

  ::std::optional< ::mlir::ArrayAttr > getArgAttrs();
  ::mlir::ArrayAttr getResAttrsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().res_attrs);
  }

  ::std::optional< ::mlir::ArrayAttr > getResAttrs();
  ::mlir::ArrayAttr getPortNamesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().portNames);
  }

  ::mlir::ArrayAttr getPortNames();
  ::mlir::ArrayAttr getPortAttributesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().portAttributes);
  }

  ::mlir::ArrayAttr getPortAttributes();
  ::mlir::IntegerAttr getPortDirectionsAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().portDirections);
  }

  ::mlir::APInt getPortDirections();
  void setFunctionTypeAttr(::mlir::TypeAttr attr) {
    getProperties().function_type = attr;
  }

  void setFunctionType(::mlir::FunctionType attrValue);
  void setArgAttrsAttr(::mlir::ArrayAttr attr) {
    getProperties().arg_attrs = attr;
  }

  void setResAttrsAttr(::mlir::ArrayAttr attr) {
    getProperties().res_attrs = attr;
  }

  void setPortNamesAttr(::mlir::ArrayAttr attr) {
    getProperties().portNames = attr;
  }

  void setPortAttributesAttr(::mlir::ArrayAttr attr) {
    getProperties().portAttributes = attr;
  }

  void setPortDirectionsAttr(::mlir::IntegerAttr attr) {
    getProperties().portDirections = attr;
  }

  ::mlir::Attribute removeArgAttrsAttr() {
      auto attr = getProperties().arg_attrs;
      getProperties().arg_attrs = {};
      return attr;
  }

  ::mlir::Attribute removeResAttrsAttr() {
      auto attr = getProperties().res_attrs;
      getProperties().res_attrs = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringAttr name, ArrayRef<PortInfo> ports);
  static ComponentOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr name, ArrayRef<PortInfo> ports);
  static ComponentOp create(::mlir::ImplicitLocOpBuilder &builder, StringAttr name, ArrayRef<PortInfo> ports);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections);
  static ComponentOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections);
  static ComponentOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections);
  static ComponentOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections);
  static ComponentOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections);
  static ComponentOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections);
  static ComponentOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections);
  static ComponentOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections);
  static ComponentOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ComponentOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ComponentOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ComponentOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ComponentOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  SmallVector<circt::calyx::PortInfo> getPortInfo();
  SmallVector<circt::calyx::PortInfo> getInputPortInfo();
  SmallVector<circt::calyx::PortInfo> getOutputPortInfo();
  StringRef getName();
  bool isComb();
  Region*getRegion();
  Block*getBodyBlock();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
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
  using mlir::detail::FunctionOpInterfaceTrait<ComponentOp>::front;
  using mlir::detail::FunctionOpInterfaceTrait<ComponentOp>::getFunctionBody;

  // Implement RegionKindInterface.
  static RegionKind getRegionKind(unsigned index) { return RegionKind::Graph;}

  /// Returns the argument types of this function.
  ArrayRef<Type> getArgumentTypes() { return getFunctionType().getInputs(); }

  /// Returns the result types of this function.
  ArrayRef<Type> getResultTypes() { return getFunctionType().getResults(); }

  /// Returns the region on the current operation that is callable.
  ::mlir::Region *getCallableRegion() {
    return &getBody();
  }

  /// Verify the type attribute of this function. Returns failure and emits
  /// an error if the attribute is invalid.
  LogicalResult verifyType() {
    auto type = getFunctionTypeAttr().getValue();
    if (!llvm::isa<FunctionType>(type))
      return emitOpError("requires '" +
                  getFunctionTypeAttrName().getValue() +
                         "' attribute of function type");
    return success();
  }

  /// Returns the WiresOp of a Calyx Component.
  WiresOp getWiresOp();

  /// Returns the ControlOp of a Calyx Component.
  ControlOp getControlOp();

  /// Gets the Done port of a Calyx component.
  Value getDonePort();

  /// Gets the Go port of a Calyx component.
  Value getGoPort();

  /// Gets the Clock port of a Calyx component.
  Value getClkPort();

  /// Gets the Reset port of a Calyx component.
  Value getResetPort();

  void getAsmBlockArgumentNames(mlir::Region &region,
                                mlir::OpAsmSetValueNameFn setNameFn);
};

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::ComponentOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::ComponentOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::ConstantOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ConstantOpGenericAdaptorBase {
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
    using valueTy = ::mlir::TypedAttr;
    valueTy value;

    auto getValue() const {
      auto &propStorage = this->value;
      return ::llvm::cast<::mlir::TypedAttr>(propStorage);
    }
    void setValue(const ::mlir::TypedAttr &propValue) {
      this->value = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.sym_name == this->sym_name &&
        rhs.value == this->value &&
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
  ConstantOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.constant", odsAttrs.getContext());
  }

  ConstantOpGenericAdaptorBase(ConstantOp op);

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
  ::mlir::TypedAttr getValueAttr() {
    auto attr = ::llvm::cast<::mlir::TypedAttr>(getProperties().value);
    return attr;
  }

  ::mlir::TypedAttr getValue();
};

} // namespace detail
template <typename RangeT>
class ConstantOpGenericAdaptor : public detail::ConstantOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ConstantOpGenericAdaptorBase;
public:
  ConstantOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ConstantOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ConstantOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ConstantOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ConstantOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ConstantOpGenericAdaptor(RangeT values, const ConstantOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ConstantOp, typename = std::enable_if_t<std::is_same_v<LateInst, ConstantOp>>>
  ConstantOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ConstantOpAdaptor : public ConstantOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ConstantOpGenericAdaptor::ConstantOpGenericAdaptor;
  ConstantOpAdaptor(ConstantOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ConstantOp : public ::mlir::Op<ConstantOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IntegerType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::ConstantLike, ::mlir::OpAsmOpInterface::Trait, ::circt::calyx::CellInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ConstantOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ConstantOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<ConstantOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<ConstantOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<ConstantOp>::getDefaultDialect;
  using ::circt::calyx::CellInterface::Trait<ConstantOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<ConstantOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<ConstantOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<ConstantOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<ConstantOp>::direction;
  using ::circt::calyx::CellInterface::Trait<ConstantOp>::portName;
  using ::circt::calyx::CellInterface::Trait<ConstantOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<ConstantOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<ConstantOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<ConstantOp>::filterInterfacePorts;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("sym_name"), ::llvm::StringRef("value")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getValueAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getValueAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("calyx.constant");
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

  ::mlir::TypedValue<::mlir::IntegerType> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(0).begin());
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
  ::mlir::TypedAttr getValueAttr() {
    return ::llvm::cast<::mlir::TypedAttr>(getProperties().value);
  }

  ::mlir::TypedAttr getValue();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  void setValueAttr(::mlir::TypedAttr attr) {
    getProperties().value = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, Attribute attr, Type type);
  static ConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, Attribute attr, Type type);
  static ConstantOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, Attribute attr, Type type);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::ConstantOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::ConstantOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::ControlOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ControlOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ControlOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.control", odsAttrs.getContext());
  }

  ControlOpGenericAdaptorBase(ControlOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class ControlOpGenericAdaptor : public detail::ControlOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ControlOpGenericAdaptorBase;
public:
  ControlOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ControlOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ControlOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ControlOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ControlOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ControlOpGenericAdaptor(RangeT values, const ControlOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ControlOp, typename = std::enable_if_t<std::is_same_v<LateInst, ControlOp>>>
  ControlOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ControlOpAdaptor : public ControlOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ControlOpGenericAdaptor::ControlOpGenericAdaptor;
  ControlOpAdaptor(ControlOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ControlOp : public ::mlir::Op<ControlOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<ComponentOp>::Impl, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::SymbolTable> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ControlOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ControlOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("calyx.control");
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static ControlOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static ControlOp create(::mlir::ImplicitLocOpBuilder &builder);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  /// Returns the body of a Calyx container.
  Block *getBodyBlock() {
    Region* region = &getOperation()->getRegion(0);
    assert(region->hasOneBlock() && "The body should have one Block.");
    return &region->front();
  }

  /// Get the InvokeOp of the ControlOp.
  SmallVector<InvokeOp, 4> getInvokeOps();
};

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::ControlOp)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::CycleOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CycleOpGenericAdaptorBase {
public:
  struct Properties {
    using endTy = ::mlir::IntegerAttr;
    endTy end;

    auto getEnd() const {
      auto &propStorage = this->end;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setEnd(const ::mlir::IntegerAttr &propValue) {
      this->end = propValue;
    }
    using startTy = ::mlir::IntegerAttr;
    startTy start;

    auto getStart() const {
      auto &propStorage = this->start;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setStart(const ::mlir::IntegerAttr &propValue) {
      this->start = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.end == this->end &&
        rhs.start == this->start &&
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
  CycleOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.cycle", odsAttrs.getContext());
  }

  CycleOpGenericAdaptorBase(CycleOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getStartAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().start);
    return attr;
  }

  uint32_t getStart();
  ::mlir::IntegerAttr getEndAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().end);
    return attr;
  }

  ::std::optional<uint32_t> getEnd();
};

} // namespace detail
template <typename RangeT>
class CycleOpGenericAdaptor : public detail::CycleOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CycleOpGenericAdaptorBase;
public:
  CycleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CycleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : CycleOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CycleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CycleOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CycleOpGenericAdaptor(RangeT values, const CycleOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CycleOp, typename = std::enable_if_t<std::is_same_v<LateInst, CycleOp>>>
  CycleOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class CycleOpAdaptor : public CycleOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CycleOpGenericAdaptor::CycleOpGenericAdaptor;
  CycleOpAdaptor(CycleOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CycleOp : public ::mlir::Op<CycleOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IntegerType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<StaticGroupOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CycleOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CycleOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("end"), ::llvm::StringRef("start")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getEndAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getEndAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getStartAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getStartAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("calyx.cycle");
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

  ::mlir::TypedValue<::mlir::IntegerType> getActive() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(0).begin());
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
  ::mlir::IntegerAttr getStartAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().start);
  }

  uint32_t getStart();
  ::mlir::IntegerAttr getEndAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().end);
  }

  ::std::optional<uint32_t> getEnd();
  void setStartAttr(::mlir::IntegerAttr attr) {
    getProperties().start = attr;
  }

  void setStart(uint32_t attrValue);
  void setEndAttr(::mlir::IntegerAttr attr) {
    getProperties().end = attr;
  }

  void setEnd(::std::optional<uint32_t> attrValue);
  ::mlir::Attribute removeEndAttr() {
      auto attr = getProperties().end;
      getProperties().end = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, uint32_t start);
  static CycleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, uint32_t start);
  static CycleOp create(::mlir::ImplicitLocOpBuilder &builder, uint32_t start);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, uint32_t start, uint32_t end);
  static CycleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, uint32_t start, uint32_t end);
  static CycleOp create(::mlir::ImplicitLocOpBuilder &builder, uint32_t start, uint32_t end);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type active, ::mlir::IntegerAttr start, /*optional*/::mlir::IntegerAttr end);
  static CycleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type active, ::mlir::IntegerAttr start, /*optional*/::mlir::IntegerAttr end);
  static CycleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type active, ::mlir::IntegerAttr start, /*optional*/::mlir::IntegerAttr end);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr start, /*optional*/::mlir::IntegerAttr end);
  static CycleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr start, /*optional*/::mlir::IntegerAttr end);
  static CycleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr start, /*optional*/::mlir::IntegerAttr end);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type active, uint32_t start, /*optional*/::mlir::IntegerAttr end);
  static CycleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type active, uint32_t start, /*optional*/::mlir::IntegerAttr end);
  static CycleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type active, uint32_t start, /*optional*/::mlir::IntegerAttr end);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, uint32_t start, /*optional*/::mlir::IntegerAttr end);
  static CycleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, uint32_t start, /*optional*/::mlir::IntegerAttr end);
  static CycleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, uint32_t start, /*optional*/::mlir::IntegerAttr end);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CycleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CycleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CycleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CycleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
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
  /// Returns the latency of the parent static group.
  uint32_t getGroupLatency();
};

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::CycleOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::CycleOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::DivSPipeLibOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DivSPipeLibOpGenericAdaptorBase {
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
  DivSPipeLibOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.std_divs_pipe", odsAttrs.getContext());
  }

  DivSPipeLibOpGenericAdaptorBase(DivSPipeLibOp op);

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
class DivSPipeLibOpGenericAdaptor : public detail::DivSPipeLibOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DivSPipeLibOpGenericAdaptorBase;
public:
  DivSPipeLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DivSPipeLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : DivSPipeLibOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DivSPipeLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : DivSPipeLibOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DivSPipeLibOpGenericAdaptor(RangeT values, const DivSPipeLibOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DivSPipeLibOp, typename = std::enable_if_t<std::is_same_v<LateInst, DivSPipeLibOp>>>
  DivSPipeLibOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class DivSPipeLibOpAdaptor : public DivSPipeLibOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DivSPipeLibOpGenericAdaptor::DivSPipeLibOpGenericAdaptor;
  DivSPipeLibOpAdaptor(DivSPipeLibOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DivSPipeLibOp : public ::mlir::Op<DivSPipeLibOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<7>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DivSPipeLibOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DivSPipeLibOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<DivSPipeLibOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<DivSPipeLibOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<DivSPipeLibOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<DivSPipeLibOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<DivSPipeLibOp>::direction;
  using ::circt::calyx::CellInterface::Trait<DivSPipeLibOp>::portName;
  using ::circt::calyx::CellInterface::Trait<DivSPipeLibOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<DivSPipeLibOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<DivSPipeLibOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<DivSPipeLibOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<DivSPipeLibOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<DivSPipeLibOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<DivSPipeLibOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.std_divs_pipe");
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

  ::mlir::TypedValue<::mlir::IntegerType> getClk() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getReset() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getGo() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(2).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getLeft() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(3).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getRight() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(4).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(5).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getDone() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(6).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static DivSPipeLibOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static DivSPipeLibOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::DivSPipeLibOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::DivSPipeLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::DivSqrtOpIEEE754 declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DivSqrtOpIEEE754GenericAdaptorBase {
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
  DivSqrtOpIEEE754GenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.ieee754.divSqrt", odsAttrs.getContext());
  }

  DivSqrtOpIEEE754GenericAdaptorBase(DivSqrtOpIEEE754 op);

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
class DivSqrtOpIEEE754GenericAdaptor : public detail::DivSqrtOpIEEE754GenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DivSqrtOpIEEE754GenericAdaptorBase;
public:
  DivSqrtOpIEEE754GenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DivSqrtOpIEEE754GenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : DivSqrtOpIEEE754GenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DivSqrtOpIEEE754GenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : DivSqrtOpIEEE754GenericAdaptor(values, attrs, Properties{}, {}) {}

  DivSqrtOpIEEE754GenericAdaptor(RangeT values, const DivSqrtOpIEEE754GenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DivSqrtOpIEEE754, typename = std::enable_if_t<std::is_same_v<LateInst, DivSqrtOpIEEE754>>>
  DivSqrtOpIEEE754GenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class DivSqrtOpIEEE754Adaptor : public DivSqrtOpIEEE754GenericAdaptor<::mlir::ValueRange> {
public:
  using DivSqrtOpIEEE754GenericAdaptor::DivSqrtOpIEEE754GenericAdaptor;
  DivSqrtOpIEEE754Adaptor(DivSqrtOpIEEE754 op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DivSqrtOpIEEE754 : public ::mlir::Op<DivSqrtOpIEEE754, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<11>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::FloatingPointOpInterface::Trait, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DivSqrtOpIEEE754Adaptor;
  template <typename RangeT>
  using GenericAdaptor = DivSqrtOpIEEE754GenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<DivSqrtOpIEEE754>::instanceName;
  using ::circt::calyx::CellInterface::Trait<DivSqrtOpIEEE754>::portIndex;
  using ::circt::calyx::CellInterface::Trait<DivSqrtOpIEEE754>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<DivSqrtOpIEEE754>::portInfo;
  using ::circt::calyx::CellInterface::Trait<DivSqrtOpIEEE754>::direction;
  using ::circt::calyx::CellInterface::Trait<DivSqrtOpIEEE754>::portName;
  using ::circt::calyx::CellInterface::Trait<DivSqrtOpIEEE754>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<DivSqrtOpIEEE754>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<DivSqrtOpIEEE754>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<DivSqrtOpIEEE754>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<DivSqrtOpIEEE754>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<DivSqrtOpIEEE754>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<DivSqrtOpIEEE754>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.ieee754.divSqrt");
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

  ::mlir::TypedValue<::mlir::IntegerType> getClk() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getReset() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getGo() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(2).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getControl() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(3).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getSqrtOp() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(4).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getLeft() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(5).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getRight() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(6).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getRoundingMode() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(7).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(8).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getExceptionalFlags() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(9).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getDone() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(10).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static DivSqrtOpIEEE754 create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static DivSqrtOpIEEE754 create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static FloatingPointStandard getFloatingPointStandard();
  static std::string getCalyxLibraryName();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::DivSqrtOpIEEE754)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::DivSqrtOpIEEE754GenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::DivUPipeLibOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DivUPipeLibOpGenericAdaptorBase {
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
  DivUPipeLibOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.std_divu_pipe", odsAttrs.getContext());
  }

  DivUPipeLibOpGenericAdaptorBase(DivUPipeLibOp op);

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
class DivUPipeLibOpGenericAdaptor : public detail::DivUPipeLibOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DivUPipeLibOpGenericAdaptorBase;
public:
  DivUPipeLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DivUPipeLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : DivUPipeLibOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DivUPipeLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : DivUPipeLibOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DivUPipeLibOpGenericAdaptor(RangeT values, const DivUPipeLibOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DivUPipeLibOp, typename = std::enable_if_t<std::is_same_v<LateInst, DivUPipeLibOp>>>
  DivUPipeLibOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class DivUPipeLibOpAdaptor : public DivUPipeLibOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DivUPipeLibOpGenericAdaptor::DivUPipeLibOpGenericAdaptor;
  DivUPipeLibOpAdaptor(DivUPipeLibOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DivUPipeLibOp : public ::mlir::Op<DivUPipeLibOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<7>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DivUPipeLibOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DivUPipeLibOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<DivUPipeLibOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<DivUPipeLibOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<DivUPipeLibOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<DivUPipeLibOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<DivUPipeLibOp>::direction;
  using ::circt::calyx::CellInterface::Trait<DivUPipeLibOp>::portName;
  using ::circt::calyx::CellInterface::Trait<DivUPipeLibOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<DivUPipeLibOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<DivUPipeLibOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<DivUPipeLibOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<DivUPipeLibOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<DivUPipeLibOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<DivUPipeLibOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.std_divu_pipe");
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

  ::mlir::TypedValue<::mlir::IntegerType> getClk() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getReset() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getGo() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(2).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getLeft() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(3).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getRight() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(4).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(5).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getDone() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(6).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static DivUPipeLibOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static DivUPipeLibOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::DivUPipeLibOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::DivUPipeLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::EnableOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class EnableOpGenericAdaptorBase {
public:
  struct Properties {
    using compiledGroupsTy = ::mlir::ArrayAttr;
    compiledGroupsTy compiledGroups;

    auto getCompiledGroups() const {
      auto &propStorage = this->compiledGroups;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setCompiledGroups(const ::mlir::ArrayAttr &propValue) {
      this->compiledGroups = propValue;
    }
    using groupNameTy = ::mlir::FlatSymbolRefAttr;
    groupNameTy groupName;

    auto getGroupName() const {
      auto &propStorage = this->groupName;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setGroupName(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->groupName = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.compiledGroups == this->compiledGroups &&
        rhs.groupName == this->groupName &&
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
  EnableOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.enable", odsAttrs.getContext());
  }

  EnableOpGenericAdaptorBase(EnableOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getGroupNameAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().groupName);
    return attr;
  }

  ::llvm::StringRef getGroupName();
  ::mlir::ArrayAttr getCompiledGroupsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().compiledGroups);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getCompiledGroups();
};

} // namespace detail
template <typename RangeT>
class EnableOpGenericAdaptor : public detail::EnableOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::EnableOpGenericAdaptorBase;
public:
  EnableOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  EnableOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : EnableOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  EnableOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : EnableOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  EnableOpGenericAdaptor(RangeT values, const EnableOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = EnableOp, typename = std::enable_if_t<std::is_same_v<LateInst, EnableOp>>>
  EnableOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class EnableOpAdaptor : public EnableOpGenericAdaptor<::mlir::ValueRange> {
public:
  using EnableOpGenericAdaptor::EnableOpGenericAdaptor;
  EnableOpAdaptor(EnableOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class EnableOp : public ::mlir::Op<EnableOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::ControlLike> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = EnableOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = EnableOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("compiledGroups"), ::llvm::StringRef("groupName")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getCompiledGroupsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getCompiledGroupsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getGroupNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getGroupNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("calyx.enable");
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
  ::mlir::FlatSymbolRefAttr getGroupNameAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().groupName);
  }

  ::llvm::StringRef getGroupName();
  ::mlir::ArrayAttr getCompiledGroupsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().compiledGroups);
  }

  ::std::optional< ::mlir::ArrayAttr > getCompiledGroups();
  void setGroupNameAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().groupName = attr;
  }

  void setGroupName(::llvm::StringRef attrValue);
  void setCompiledGroupsAttr(::mlir::ArrayAttr attr) {
    getProperties().compiledGroups = attr;
  }

  ::mlir::Attribute removeCompiledGroupsAttr() {
      auto attr = getProperties().compiledGroups;
      getProperties().compiledGroups = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef groupName);
  static EnableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef groupName);
  static EnableOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef groupName);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::FlatSymbolRefAttr groupName, /*optional*/::mlir::ArrayAttr compiledGroups);
  static EnableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::FlatSymbolRefAttr groupName, /*optional*/::mlir::ArrayAttr compiledGroups);
  static EnableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::FlatSymbolRefAttr groupName, /*optional*/::mlir::ArrayAttr compiledGroups);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr groupName, /*optional*/::mlir::ArrayAttr compiledGroups);
  static EnableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr groupName, /*optional*/::mlir::ArrayAttr compiledGroups);
  static EnableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr groupName, /*optional*/::mlir::ArrayAttr compiledGroups);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef groupName, /*optional*/::mlir::ArrayAttr compiledGroups);
  static EnableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef groupName, /*optional*/::mlir::ArrayAttr compiledGroups);
  static EnableOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef groupName, /*optional*/::mlir::ArrayAttr compiledGroups);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef groupName, /*optional*/::mlir::ArrayAttr compiledGroups);
  static EnableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef groupName, /*optional*/::mlir::ArrayAttr compiledGroups);
  static EnableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef groupName, /*optional*/::mlir::ArrayAttr compiledGroups);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static EnableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static EnableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static EnableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static EnableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::EnableOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::EnableOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::EqLibOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class EqLibOpGenericAdaptorBase {
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
  EqLibOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.std_eq", odsAttrs.getContext());
  }

  EqLibOpGenericAdaptorBase(EqLibOp op);

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
class EqLibOpGenericAdaptor : public detail::EqLibOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::EqLibOpGenericAdaptorBase;
public:
  EqLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  EqLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : EqLibOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  EqLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : EqLibOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  EqLibOpGenericAdaptor(RangeT values, const EqLibOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = EqLibOp, typename = std::enable_if_t<std::is_same_v<LateInst, EqLibOp>>>
  EqLibOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class EqLibOpAdaptor : public EqLibOpGenericAdaptor<::mlir::ValueRange> {
public:
  using EqLibOpGenericAdaptor::EqLibOpGenericAdaptor;
  EqLibOpAdaptor(EqLibOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class EqLibOp : public ::mlir::Op<EqLibOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<3>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::Combinational, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = EqLibOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = EqLibOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<EqLibOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<EqLibOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<EqLibOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<EqLibOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<EqLibOp>::direction;
  using ::circt::calyx::CellInterface::Trait<EqLibOp>::portName;
  using ::circt::calyx::CellInterface::Trait<EqLibOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<EqLibOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<EqLibOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<EqLibOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<EqLibOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<EqLibOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<EqLibOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.std_eq");
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

  ::mlir::TypedValue<::mlir::Type> getLeft() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getRight() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(2).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static EqLibOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static EqLibOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::EqLibOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::EqLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::ExtSILibOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ExtSILibOpGenericAdaptorBase {
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
  ExtSILibOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.std_signext", odsAttrs.getContext());
  }

  ExtSILibOpGenericAdaptorBase(ExtSILibOp op);

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
class ExtSILibOpGenericAdaptor : public detail::ExtSILibOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ExtSILibOpGenericAdaptorBase;
public:
  ExtSILibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ExtSILibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ExtSILibOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ExtSILibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ExtSILibOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ExtSILibOpGenericAdaptor(RangeT values, const ExtSILibOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ExtSILibOp, typename = std::enable_if_t<std::is_same_v<LateInst, ExtSILibOp>>>
  ExtSILibOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ExtSILibOpAdaptor : public ExtSILibOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ExtSILibOpGenericAdaptor::ExtSILibOpGenericAdaptor;
  ExtSILibOpAdaptor(ExtSILibOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ExtSILibOp : public ::mlir::Op<ExtSILibOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<2>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::Combinational, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ExtSILibOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ExtSILibOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<ExtSILibOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<ExtSILibOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<ExtSILibOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<ExtSILibOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<ExtSILibOp>::direction;
  using ::circt::calyx::CellInterface::Trait<ExtSILibOp>::portName;
  using ::circt::calyx::CellInterface::Trait<ExtSILibOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<ExtSILibOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<ExtSILibOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<ExtSILibOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<ExtSILibOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<ExtSILibOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<ExtSILibOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.std_signext");
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

  ::mlir::TypedValue<::mlir::IntegerType> getIn() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(1).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static ExtSILibOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static ExtSILibOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::ExtSILibOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::ExtSILibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::FpToIntOpIEEE754 declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FpToIntOpIEEE754GenericAdaptorBase {
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
  FpToIntOpIEEE754GenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.ieee754.fpToInt", odsAttrs.getContext());
  }

  FpToIntOpIEEE754GenericAdaptorBase(FpToIntOpIEEE754 op);

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
class FpToIntOpIEEE754GenericAdaptor : public detail::FpToIntOpIEEE754GenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FpToIntOpIEEE754GenericAdaptorBase;
public:
  FpToIntOpIEEE754GenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FpToIntOpIEEE754GenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : FpToIntOpIEEE754GenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FpToIntOpIEEE754GenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FpToIntOpIEEE754GenericAdaptor(values, attrs, Properties{}, {}) {}

  FpToIntOpIEEE754GenericAdaptor(RangeT values, const FpToIntOpIEEE754GenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FpToIntOpIEEE754, typename = std::enable_if_t<std::is_same_v<LateInst, FpToIntOpIEEE754>>>
  FpToIntOpIEEE754GenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class FpToIntOpIEEE754Adaptor : public FpToIntOpIEEE754GenericAdaptor<::mlir::ValueRange> {
public:
  using FpToIntOpIEEE754GenericAdaptor::FpToIntOpIEEE754GenericAdaptor;
  FpToIntOpIEEE754Adaptor(FpToIntOpIEEE754 op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FpToIntOpIEEE754 : public ::mlir::Op<FpToIntOpIEEE754, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<7>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::FloatingPointOpInterface::Trait, ::circt::calyx::Combinational, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FpToIntOpIEEE754Adaptor;
  template <typename RangeT>
  using GenericAdaptor = FpToIntOpIEEE754GenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<FpToIntOpIEEE754>::instanceName;
  using ::circt::calyx::CellInterface::Trait<FpToIntOpIEEE754>::portIndex;
  using ::circt::calyx::CellInterface::Trait<FpToIntOpIEEE754>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<FpToIntOpIEEE754>::portInfo;
  using ::circt::calyx::CellInterface::Trait<FpToIntOpIEEE754>::direction;
  using ::circt::calyx::CellInterface::Trait<FpToIntOpIEEE754>::portName;
  using ::circt::calyx::CellInterface::Trait<FpToIntOpIEEE754>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<FpToIntOpIEEE754>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<FpToIntOpIEEE754>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<FpToIntOpIEEE754>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<FpToIntOpIEEE754>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<FpToIntOpIEEE754>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<FpToIntOpIEEE754>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.ieee754.fpToInt");
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

  ::mlir::TypedValue<::mlir::IntegerType> getClk() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getReset() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getGo() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(2).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getIn() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(3).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getSignedOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(4).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(5).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getDone() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(6).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static FpToIntOpIEEE754 create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static FpToIntOpIEEE754 create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static FloatingPointStandard getFloatingPointStandard();
  static std::string getCalyxLibraryName();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::FpToIntOpIEEE754)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::FpToIntOpIEEE754GenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::GeLibOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GeLibOpGenericAdaptorBase {
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
  GeLibOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.std_ge", odsAttrs.getContext());
  }

  GeLibOpGenericAdaptorBase(GeLibOp op);

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
class GeLibOpGenericAdaptor : public detail::GeLibOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GeLibOpGenericAdaptorBase;
public:
  GeLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GeLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : GeLibOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GeLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GeLibOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GeLibOpGenericAdaptor(RangeT values, const GeLibOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GeLibOp, typename = std::enable_if_t<std::is_same_v<LateInst, GeLibOp>>>
  GeLibOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class GeLibOpAdaptor : public GeLibOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GeLibOpGenericAdaptor::GeLibOpGenericAdaptor;
  GeLibOpAdaptor(GeLibOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GeLibOp : public ::mlir::Op<GeLibOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<3>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::Combinational, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GeLibOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GeLibOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<GeLibOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<GeLibOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<GeLibOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<GeLibOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<GeLibOp>::direction;
  using ::circt::calyx::CellInterface::Trait<GeLibOp>::portName;
  using ::circt::calyx::CellInterface::Trait<GeLibOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<GeLibOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<GeLibOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<GeLibOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<GeLibOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<GeLibOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<GeLibOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.std_ge");
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

  ::mlir::TypedValue<::mlir::Type> getLeft() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getRight() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(2).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static GeLibOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static GeLibOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::GeLibOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::GeLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::GroupDoneOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GroupDoneOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  GroupDoneOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.group_done", odsAttrs.getContext());
  }

  GroupDoneOpGenericAdaptorBase(GroupDoneOp op);

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
class GroupDoneOpGenericAdaptor : public detail::GroupDoneOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GroupDoneOpGenericAdaptorBase;
  static constexpr int odsIndex_src = 0;
  static constexpr int odsIndex_guard = 1;
public:
  GroupDoneOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GroupDoneOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : GroupDoneOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GroupDoneOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GroupDoneOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GroupDoneOpGenericAdaptor(RangeT values, const GroupDoneOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GroupDoneOp, typename = std::enable_if_t<std::is_same_v<LateInst, GroupDoneOp>>>
  GroupDoneOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getSrc() {
    return (*getODSOperands(0).begin());
  }

  ValueT getGuard() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class GroupDoneOpAdaptor : public GroupDoneOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GroupDoneOpGenericAdaptor::GroupDoneOpGenericAdaptor;
  GroupDoneOpAdaptor(GroupDoneOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GroupDoneOp : public ::mlir::Op<GroupDoneOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::HasParent<GroupOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GroupDoneOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GroupDoneOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_src = 0;
  static constexpr int odsIndex_guard = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("calyx.group_done");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getSrc() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getGuard() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::OpOperand &getSrcMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getGuardMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value src);
  static GroupDoneOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value src);
  static GroupDoneOp create(::mlir::ImplicitLocOpBuilder &builder, Value src);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value src, /*optional*/::mlir::Value guard);
  static GroupDoneOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value src, /*optional*/::mlir::Value guard);
  static GroupDoneOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value src, /*optional*/::mlir::Value guard);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value src, /*optional*/::mlir::Value guard);
  static GroupDoneOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value src, /*optional*/::mlir::Value guard);
  static GroupDoneOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value src, /*optional*/::mlir::Value guard);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GroupDoneOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GroupDoneOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GroupDoneOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GroupDoneOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
public:
};

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::GroupDoneOp)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::GroupGoOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GroupGoOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  GroupGoOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.group_go", odsAttrs.getContext());
  }

  GroupGoOpGenericAdaptorBase(GroupGoOp op);

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
class GroupGoOpGenericAdaptor : public detail::GroupGoOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GroupGoOpGenericAdaptorBase;
  static constexpr int odsIndex_src = 0;
  static constexpr int odsIndex_guard = 1;
public:
  GroupGoOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GroupGoOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : GroupGoOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GroupGoOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GroupGoOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GroupGoOpGenericAdaptor(RangeT values, const GroupGoOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GroupGoOp, typename = std::enable_if_t<std::is_same_v<LateInst, GroupGoOp>>>
  GroupGoOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getSrc() {
    return (*getODSOperands(0).begin());
  }

  ValueT getGuard() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class GroupGoOpAdaptor : public GroupGoOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GroupGoOpGenericAdaptor::GroupGoOpGenericAdaptor;
  GroupGoOpAdaptor(GroupGoOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GroupGoOp : public ::mlir::Op<GroupGoOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IntegerType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::HasParent<GroupOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GroupGoOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GroupGoOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_src = 0;
  static constexpr int odsIndex_guard = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<GroupGoOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<GroupGoOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<GroupGoOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("calyx.group_go");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getSrc() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getGuard() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::OpOperand &getSrcMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getGuardMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value src);
  static GroupGoOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value src);
  static GroupGoOp create(::mlir::ImplicitLocOpBuilder &builder, Value src);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::Value src, /*optional*/::mlir::Value guard);
  static GroupGoOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::Value src, /*optional*/::mlir::Value guard);
  static GroupGoOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::Value src, /*optional*/::mlir::Value guard);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value src, /*optional*/::mlir::Value guard);
  static GroupGoOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value src, /*optional*/::mlir::Value guard);
  static GroupGoOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value src, /*optional*/::mlir::Value guard);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GroupGoOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GroupGoOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GroupGoOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GroupGoOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
public:
};

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::GroupGoOp)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::GroupOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GroupOpGenericAdaptorBase {
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
  GroupOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.group", odsAttrs.getContext());
  }

  GroupOpGenericAdaptorBase(GroupOp op);

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
class GroupOpGenericAdaptor : public detail::GroupOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GroupOpGenericAdaptorBase;
public:
  GroupOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GroupOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : GroupOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GroupOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GroupOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GroupOpGenericAdaptor(RangeT values, const GroupOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GroupOp, typename = std::enable_if_t<std::is_same_v<LateInst, GroupOp>>>
  GroupOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class GroupOpAdaptor : public GroupOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GroupOpGenericAdaptor::GroupOpGenericAdaptor;
  GroupOpAdaptor(GroupOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GroupOp : public ::mlir::Op<GroupOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<WiresOp>::Impl, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::GroupInterface::Trait, ::mlir::RegionKindInterface::Trait, ::mlir::SymbolOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GroupOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GroupOpGenericAdaptor<RangeT>;
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
    return ::llvm::StringLiteral("calyx.group");
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name);
  static GroupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name);
  static GroupOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringAttr sym_name);
  static GroupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr sym_name);
  static GroupOp create(::mlir::ImplicitLocOpBuilder &builder, StringAttr sym_name);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  LogicalResult drivesPort(Value port);
  LogicalResult drivesAllPorts(ValueRange ports);
  LogicalResult drivesAnyPort(ValueRange ports);
  LogicalResult readsAnyPort(ValueRange ports);
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
  static RegionKind getRegionKind(unsigned index) { return RegionKind::Graph; }

  /// Returns the GroupGoOp for this group.
  GroupGoOp getGoOp();

  /// Returns the GroupDoneOp for this group.
  GroupDoneOp getDoneOp();

  /// Returns the body of a Calyx component.
  Block *getBodyBlock() {
    Region* region = &getOperation()->getRegion(0);
    assert(region->hasOneBlock() && "The body should have one Block.");
    return &region->front();
  }

};

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::GroupOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::GroupOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::GtLibOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GtLibOpGenericAdaptorBase {
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
  GtLibOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.std_gt", odsAttrs.getContext());
  }

  GtLibOpGenericAdaptorBase(GtLibOp op);

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
class GtLibOpGenericAdaptor : public detail::GtLibOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GtLibOpGenericAdaptorBase;
public:
  GtLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GtLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : GtLibOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GtLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GtLibOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GtLibOpGenericAdaptor(RangeT values, const GtLibOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GtLibOp, typename = std::enable_if_t<std::is_same_v<LateInst, GtLibOp>>>
  GtLibOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class GtLibOpAdaptor : public GtLibOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GtLibOpGenericAdaptor::GtLibOpGenericAdaptor;
  GtLibOpAdaptor(GtLibOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GtLibOp : public ::mlir::Op<GtLibOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<3>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::Combinational, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GtLibOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GtLibOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<GtLibOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<GtLibOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<GtLibOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<GtLibOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<GtLibOp>::direction;
  using ::circt::calyx::CellInterface::Trait<GtLibOp>::portName;
  using ::circt::calyx::CellInterface::Trait<GtLibOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<GtLibOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<GtLibOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<GtLibOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<GtLibOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<GtLibOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<GtLibOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.std_gt");
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

  ::mlir::TypedValue<::mlir::Type> getLeft() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getRight() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(2).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static GtLibOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static GtLibOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::GtLibOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::GtLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::IfOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class IfOpGenericAdaptorBase {
public:
  struct Properties {
    using groupNameTy = ::mlir::FlatSymbolRefAttr;
    groupNameTy groupName;

    auto getGroupName() const {
      auto &propStorage = this->groupName;
      return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setGroupName(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->groupName = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.groupName == this->groupName &&
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
  IfOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.if", odsAttrs.getContext());
  }

  IfOpGenericAdaptorBase(IfOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getGroupNameAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().groupName);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getGroupName();
  ::mlir::Region &getThenRegion() {
    return *odsRegions[0];
  }

  ::mlir::Region &getElseRegion() {
    return *odsRegions[1];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class IfOpGenericAdaptor : public detail::IfOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::IfOpGenericAdaptorBase;
  static constexpr int odsIndex_cond = 0;
public:
  IfOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  IfOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : IfOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  IfOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : IfOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  IfOpGenericAdaptor(RangeT values, const IfOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = IfOp, typename = std::enable_if_t<std::is_same_v<LateInst, IfOp>>>
  IfOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getCond() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class IfOpAdaptor : public IfOpGenericAdaptor<::mlir::ValueRange> {
public:
  using IfOpGenericAdaptor::IfOpGenericAdaptor;
  IfOpAdaptor(IfOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class IfOp : public ::mlir::Op<IfOp, ::mlir::OpTrait::NRegions<2>::Impl, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::ControlLike, ::circt::calyx::IfInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = IfOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = IfOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_cond = 0;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::IfInterface::Trait<IfOp>::thenBodyExists;
  using ::circt::calyx::IfInterface::Trait<IfOp>::elseBodyExists;
  using ::circt::calyx::IfInterface::Trait<IfOp>::getThenBody;
  using ::circt::calyx::IfInterface::Trait<IfOp>::getElseBody;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("groupName")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getGroupNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getGroupNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("calyx.if");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getCond() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getCondMutable() {
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

  ::mlir::Region &getThenRegion() {
    return (*this)->getRegion(0);
  }

  ::mlir::Region &getElseRegion() {
    return (*this)->getRegion(1);
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
  ::mlir::FlatSymbolRefAttr getGroupNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().groupName);
  }

  ::std::optional< ::llvm::StringRef > getGroupName();
  void setGroupNameAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().groupName = attr;
  }

  void setGroupName(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeGroupNameAttr() {
      auto attr = getProperties().groupName;
      getProperties().groupName = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value cond, FlatSymbolRefAttr groupName = nullptr, bool initializeElseBody = false);
  static IfOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value cond, FlatSymbolRefAttr groupName = nullptr, bool initializeElseBody = false);
  static IfOp create(::mlir::ImplicitLocOpBuilder &builder, Value cond, FlatSymbolRefAttr groupName = nullptr, bool initializeElseBody = false);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
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
  /// Returns the body of a Calyx container.
  Block *getBodyBlock() {
    Region* region = &getOperation()->getRegion(0);
    assert(region->hasOneBlock() && "The body should have one Block.");
    return &region->front();
  }
};

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::IfOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::IfOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::InstanceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class InstanceOpGenericAdaptorBase {
public:
  struct Properties {
    using componentNameTy = ::mlir::FlatSymbolRefAttr;
    componentNameTy componentName;

    auto getComponentName() const {
      auto &propStorage = this->componentName;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setComponentName(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->componentName = propValue;
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
        rhs.componentName == this->componentName &&
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
  InstanceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.instance", odsAttrs.getContext());
  }

  InstanceOpGenericAdaptorBase(InstanceOp op);

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
  ::mlir::FlatSymbolRefAttr getComponentNameAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().componentName);
    return attr;
  }

  ::llvm::StringRef getComponentName();
};

} // namespace detail
template <typename RangeT>
class InstanceOpGenericAdaptor : public detail::InstanceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::InstanceOpGenericAdaptorBase;
public:
  InstanceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  InstanceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : InstanceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  InstanceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : InstanceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  InstanceOpGenericAdaptor(RangeT values, const InstanceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = InstanceOp, typename = std::enable_if_t<std::is_same_v<LateInst, InstanceOp>>>
  InstanceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class InstanceOpAdaptor : public InstanceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using InstanceOpGenericAdaptor::InstanceOpGenericAdaptor;
  InstanceOpAdaptor(InstanceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class InstanceOp : public ::mlir::Op<InstanceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = InstanceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = InstanceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<InstanceOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<InstanceOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<InstanceOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<InstanceOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<InstanceOp>::direction;
  using ::circt::calyx::CellInterface::Trait<InstanceOp>::portName;
  using ::circt::calyx::CellInterface::Trait<InstanceOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<InstanceOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<InstanceOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<InstanceOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<InstanceOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<InstanceOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<InstanceOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("componentName"), ::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getComponentNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getComponentNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("calyx.instance");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getResults() {
    return getODSResults(0);
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
  ::mlir::FlatSymbolRefAttr getComponentNameAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().componentName);
  }

  ::llvm::StringRef getComponentName();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  void setComponentNameAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().componentName = attr;
  }

  void setComponentName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::StringAttr sym_name, ::mlir::FlatSymbolRefAttr componentName);
  static InstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::StringAttr sym_name, ::mlir::FlatSymbolRefAttr componentName);
  static InstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::StringAttr sym_name, ::mlir::FlatSymbolRefAttr componentName);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::llvm::StringRef sym_name, ::llvm::StringRef componentName);
  static InstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::llvm::StringRef sym_name, ::llvm::StringRef componentName);
  static InstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::llvm::StringRef sym_name, ::llvm::StringRef componentName);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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
  /// Lookup the component for the symbol. This returns null on
  /// invalid IR.
  ComponentInterface getReferencedComponent();
};

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::InstanceOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::InstanceOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::IntToFpOpIEEE754 declarations
//===----------------------------------------------------------------------===//

namespace detail {

class IntToFpOpIEEE754GenericAdaptorBase {
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
  IntToFpOpIEEE754GenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.ieee754.intToFp", odsAttrs.getContext());
  }

  IntToFpOpIEEE754GenericAdaptorBase(IntToFpOpIEEE754 op);

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
class IntToFpOpIEEE754GenericAdaptor : public detail::IntToFpOpIEEE754GenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::IntToFpOpIEEE754GenericAdaptorBase;
public:
  IntToFpOpIEEE754GenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  IntToFpOpIEEE754GenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : IntToFpOpIEEE754GenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  IntToFpOpIEEE754GenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : IntToFpOpIEEE754GenericAdaptor(values, attrs, Properties{}, {}) {}

  IntToFpOpIEEE754GenericAdaptor(RangeT values, const IntToFpOpIEEE754GenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = IntToFpOpIEEE754, typename = std::enable_if_t<std::is_same_v<LateInst, IntToFpOpIEEE754>>>
  IntToFpOpIEEE754GenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class IntToFpOpIEEE754Adaptor : public IntToFpOpIEEE754GenericAdaptor<::mlir::ValueRange> {
public:
  using IntToFpOpIEEE754GenericAdaptor::IntToFpOpIEEE754GenericAdaptor;
  IntToFpOpIEEE754Adaptor(IntToFpOpIEEE754 op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class IntToFpOpIEEE754 : public ::mlir::Op<IntToFpOpIEEE754, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<7>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::FloatingPointOpInterface::Trait, ::circt::calyx::Combinational, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = IntToFpOpIEEE754Adaptor;
  template <typename RangeT>
  using GenericAdaptor = IntToFpOpIEEE754GenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<IntToFpOpIEEE754>::instanceName;
  using ::circt::calyx::CellInterface::Trait<IntToFpOpIEEE754>::portIndex;
  using ::circt::calyx::CellInterface::Trait<IntToFpOpIEEE754>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<IntToFpOpIEEE754>::portInfo;
  using ::circt::calyx::CellInterface::Trait<IntToFpOpIEEE754>::direction;
  using ::circt::calyx::CellInterface::Trait<IntToFpOpIEEE754>::portName;
  using ::circt::calyx::CellInterface::Trait<IntToFpOpIEEE754>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<IntToFpOpIEEE754>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<IntToFpOpIEEE754>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<IntToFpOpIEEE754>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<IntToFpOpIEEE754>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<IntToFpOpIEEE754>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<IntToFpOpIEEE754>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.ieee754.intToFp");
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

  ::mlir::TypedValue<::mlir::IntegerType> getClk() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getReset() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getGo() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(2).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getIn() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(3).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getSignedIn() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(4).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(5).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getDone() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(6).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static IntToFpOpIEEE754 create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static IntToFpOpIEEE754 create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static FloatingPointStandard getFloatingPointStandard();
  static std::string getCalyxLibraryName();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::IntToFpOpIEEE754)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::IntToFpOpIEEE754GenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::InvokeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class InvokeOpGenericAdaptorBase {
public:
  struct Properties {
    using calleeTy = ::mlir::FlatSymbolRefAttr;
    calleeTy callee;

    auto getCallee() const {
      auto &propStorage = this->callee;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setCallee(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->callee = propValue;
    }
    using inputNamesTy = ::mlir::ArrayAttr;
    inputNamesTy inputNames;

    auto getInputNames() const {
      auto &propStorage = this->inputNames;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setInputNames(const ::mlir::ArrayAttr &propValue) {
      this->inputNames = propValue;
    }
    using portNamesTy = ::mlir::ArrayAttr;
    portNamesTy portNames;

    auto getPortNames() const {
      auto &propStorage = this->portNames;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setPortNames(const ::mlir::ArrayAttr &propValue) {
      this->portNames = propValue;
    }
    using refCellsMapTy = ::mlir::ArrayAttr;
    refCellsMapTy refCellsMap;

    auto getRefCellsMap() const {
      auto &propStorage = this->refCellsMap;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setRefCellsMap(const ::mlir::ArrayAttr &propValue) {
      this->refCellsMap = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.callee == this->callee &&
        rhs.inputNames == this->inputNames &&
        rhs.portNames == this->portNames &&
        rhs.refCellsMap == this->refCellsMap &&
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
  InvokeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.invoke", odsAttrs.getContext());
  }

  InvokeOpGenericAdaptorBase(InvokeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getCalleeAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().callee);
    return attr;
  }

  ::llvm::StringRef getCallee();
  ::mlir::ArrayAttr getRefCellsMapAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().refCellsMap);
    return attr;
  }

  ::mlir::ArrayAttr getRefCellsMap();
  ::mlir::ArrayAttr getPortNamesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().portNames);
    return attr;
  }

  ::mlir::ArrayAttr getPortNames();
  ::mlir::ArrayAttr getInputNamesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().inputNames);
    return attr;
  }

  ::mlir::ArrayAttr getInputNames();
};

} // namespace detail
template <typename RangeT>
class InvokeOpGenericAdaptor : public detail::InvokeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::InvokeOpGenericAdaptorBase;
  static constexpr int odsIndex_ports = 0;
  static constexpr int odsIndex_inputs = 1;
public:
  InvokeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  InvokeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : InvokeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  InvokeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : InvokeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  InvokeOpGenericAdaptor(RangeT values, const InvokeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = InvokeOp, typename = std::enable_if_t<std::is_same_v<LateInst, InvokeOp>>>
  InvokeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getPorts() {
    return getODSOperands(0);
  }

  RangeT getInputs() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class InvokeOpAdaptor : public InvokeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using InvokeOpGenericAdaptor::InvokeOpGenericAdaptor;
  InvokeOpAdaptor(InvokeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class InvokeOp : public ::mlir::Op<InvokeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::ControlLike> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = InvokeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = InvokeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_ports = 0;
  static constexpr int odsIndex_inputs = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("callee"), ::llvm::StringRef("inputNames"), ::llvm::StringRef("portNames"), ::llvm::StringRef("refCellsMap")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getCalleeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getCalleeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getInputNamesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getInputNamesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getPortNamesAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getPortNamesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getRefCellsMapAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getRefCellsMapAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("calyx.invoke");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getPorts() {
    return getODSOperands(0);
  }

  ::mlir::Operation::operand_range getInputs() {
    return getODSOperands(1);
  }

  ::mlir::MutableOperandRange getPortsMutable();
  ::mlir::MutableOperandRange getInputsMutable();
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
  ::mlir::FlatSymbolRefAttr getCalleeAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().callee);
  }

  ::llvm::StringRef getCallee();
  ::mlir::ArrayAttr getRefCellsMapAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().refCellsMap);
  }

  ::mlir::ArrayAttr getRefCellsMap();
  ::mlir::ArrayAttr getPortNamesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().portNames);
  }

  ::mlir::ArrayAttr getPortNames();
  ::mlir::ArrayAttr getInputNamesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().inputNames);
  }

  ::mlir::ArrayAttr getInputNames();
  void setCalleeAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().callee = attr;
  }

  void setCallee(::llvm::StringRef attrValue);
  void setRefCellsMapAttr(::mlir::ArrayAttr attr) {
    getProperties().refCellsMap = attr;
  }

  void setPortNamesAttr(::mlir::ArrayAttr attr) {
    getProperties().portNames = attr;
  }

  void setInputNamesAttr(::mlir::ArrayAttr attr) {
    getProperties().inputNames = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::FlatSymbolRefAttr callee, ::mlir::ValueRange ports, ::mlir::ValueRange inputs, ::mlir::ArrayAttr refCellsMap, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr inputNames);
  static InvokeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::FlatSymbolRefAttr callee, ::mlir::ValueRange ports, ::mlir::ValueRange inputs, ::mlir::ArrayAttr refCellsMap, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr inputNames);
  static InvokeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::FlatSymbolRefAttr callee, ::mlir::ValueRange ports, ::mlir::ValueRange inputs, ::mlir::ArrayAttr refCellsMap, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr inputNames);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr callee, ::mlir::ValueRange ports, ::mlir::ValueRange inputs, ::mlir::ArrayAttr refCellsMap, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr inputNames);
  static InvokeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr callee, ::mlir::ValueRange ports, ::mlir::ValueRange inputs, ::mlir::ArrayAttr refCellsMap, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr inputNames);
  static InvokeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr callee, ::mlir::ValueRange ports, ::mlir::ValueRange inputs, ::mlir::ArrayAttr refCellsMap, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr inputNames);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef callee, ::mlir::ValueRange ports, ::mlir::ValueRange inputs, ::mlir::ArrayAttr refCellsMap, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr inputNames);
  static InvokeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef callee, ::mlir::ValueRange ports, ::mlir::ValueRange inputs, ::mlir::ArrayAttr refCellsMap, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr inputNames);
  static InvokeOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef callee, ::mlir::ValueRange ports, ::mlir::ValueRange inputs, ::mlir::ArrayAttr refCellsMap, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr inputNames);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef callee, ::mlir::ValueRange ports, ::mlir::ValueRange inputs, ::mlir::ArrayAttr refCellsMap, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr inputNames);
  static InvokeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef callee, ::mlir::ValueRange ports, ::mlir::ValueRange inputs, ::mlir::ArrayAttr refCellsMap, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr inputNames);
  static InvokeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef callee, ::mlir::ValueRange ports, ::mlir::ValueRange inputs, ::mlir::ArrayAttr refCellsMap, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr inputNames);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InvokeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InvokeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InvokeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InvokeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
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
  // Get the go port of the invoked component.
  Value getInstGoValue();
  // Get the done port of the invoked component.
  Value getInstDoneValue();
};

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::InvokeOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::InvokeOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::LeLibOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LeLibOpGenericAdaptorBase {
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
  LeLibOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.std_le", odsAttrs.getContext());
  }

  LeLibOpGenericAdaptorBase(LeLibOp op);

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
class LeLibOpGenericAdaptor : public detail::LeLibOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LeLibOpGenericAdaptorBase;
public:
  LeLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  LeLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : LeLibOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  LeLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : LeLibOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  LeLibOpGenericAdaptor(RangeT values, const LeLibOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = LeLibOp, typename = std::enable_if_t<std::is_same_v<LateInst, LeLibOp>>>
  LeLibOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class LeLibOpAdaptor : public LeLibOpGenericAdaptor<::mlir::ValueRange> {
public:
  using LeLibOpGenericAdaptor::LeLibOpGenericAdaptor;
  LeLibOpAdaptor(LeLibOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class LeLibOp : public ::mlir::Op<LeLibOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<3>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::Combinational, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LeLibOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LeLibOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<LeLibOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<LeLibOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<LeLibOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<LeLibOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<LeLibOp>::direction;
  using ::circt::calyx::CellInterface::Trait<LeLibOp>::portName;
  using ::circt::calyx::CellInterface::Trait<LeLibOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<LeLibOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<LeLibOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<LeLibOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<LeLibOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<LeLibOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<LeLibOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.std_le");
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

  ::mlir::TypedValue<::mlir::Type> getLeft() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getRight() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(2).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static LeLibOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static LeLibOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::LeLibOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::LeLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::LshLibOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LshLibOpGenericAdaptorBase {
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
  LshLibOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.std_lsh", odsAttrs.getContext());
  }

  LshLibOpGenericAdaptorBase(LshLibOp op);

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
class LshLibOpGenericAdaptor : public detail::LshLibOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LshLibOpGenericAdaptorBase;
public:
  LshLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  LshLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : LshLibOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  LshLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : LshLibOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  LshLibOpGenericAdaptor(RangeT values, const LshLibOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = LshLibOp, typename = std::enable_if_t<std::is_same_v<LateInst, LshLibOp>>>
  LshLibOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class LshLibOpAdaptor : public LshLibOpGenericAdaptor<::mlir::ValueRange> {
public:
  using LshLibOpGenericAdaptor::LshLibOpGenericAdaptor;
  LshLibOpAdaptor(LshLibOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class LshLibOp : public ::mlir::Op<LshLibOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<3>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::Combinational, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LshLibOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LshLibOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<LshLibOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<LshLibOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<LshLibOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<LshLibOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<LshLibOp>::direction;
  using ::circt::calyx::CellInterface::Trait<LshLibOp>::portName;
  using ::circt::calyx::CellInterface::Trait<LshLibOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<LshLibOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<LshLibOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<LshLibOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<LshLibOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<LshLibOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<LshLibOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.std_lsh");
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

  ::mlir::TypedValue<::mlir::Type> getLeft() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getRight() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(2).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static LshLibOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static LshLibOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::LshLibOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::LshLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::LtLibOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LtLibOpGenericAdaptorBase {
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
  LtLibOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.std_lt", odsAttrs.getContext());
  }

  LtLibOpGenericAdaptorBase(LtLibOp op);

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
class LtLibOpGenericAdaptor : public detail::LtLibOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LtLibOpGenericAdaptorBase;
public:
  LtLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  LtLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : LtLibOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  LtLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : LtLibOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  LtLibOpGenericAdaptor(RangeT values, const LtLibOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = LtLibOp, typename = std::enable_if_t<std::is_same_v<LateInst, LtLibOp>>>
  LtLibOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class LtLibOpAdaptor : public LtLibOpGenericAdaptor<::mlir::ValueRange> {
public:
  using LtLibOpGenericAdaptor::LtLibOpGenericAdaptor;
  LtLibOpAdaptor(LtLibOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class LtLibOp : public ::mlir::Op<LtLibOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<3>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::Combinational, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LtLibOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LtLibOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<LtLibOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<LtLibOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<LtLibOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<LtLibOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<LtLibOp>::direction;
  using ::circt::calyx::CellInterface::Trait<LtLibOp>::portName;
  using ::circt::calyx::CellInterface::Trait<LtLibOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<LtLibOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<LtLibOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<LtLibOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<LtLibOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<LtLibOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<LtLibOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.std_lt");
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

  ::mlir::TypedValue<::mlir::Type> getLeft() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getRight() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(2).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static LtLibOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static LtLibOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::LtLibOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::LtLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::MemoryOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MemoryOpGenericAdaptorBase {
public:
  struct Properties {
    using addrSizesTy = ::mlir::ArrayAttr;
    addrSizesTy addrSizes;

    auto getAddrSizes() const {
      auto &propStorage = this->addrSizes;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setAddrSizes(const ::mlir::ArrayAttr &propValue) {
      this->addrSizes = propValue;
    }
    using sizesTy = ::mlir::ArrayAttr;
    sizesTy sizes;

    auto getSizes() const {
      auto &propStorage = this->sizes;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setSizes(const ::mlir::ArrayAttr &propValue) {
      this->sizes = propValue;
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
    using widthTy = ::mlir::IntegerAttr;
    widthTy width;

    auto getWidth() const {
      auto &propStorage = this->width;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setWidth(const ::mlir::IntegerAttr &propValue) {
      this->width = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.addrSizes == this->addrSizes &&
        rhs.sizes == this->sizes &&
        rhs.sym_name == this->sym_name &&
        rhs.width == this->width &&
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
  MemoryOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.memory", odsAttrs.getContext());
  }

  MemoryOpGenericAdaptorBase(MemoryOp op);

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
  ::mlir::IntegerAttr getWidthAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().width);
    return attr;
  }

  uint64_t getWidth();
  ::mlir::ArrayAttr getSizesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().sizes);
    return attr;
  }

  ::mlir::ArrayAttr getSizes();
  ::mlir::ArrayAttr getAddrSizesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().addrSizes);
    return attr;
  }

  ::mlir::ArrayAttr getAddrSizes();
};

} // namespace detail
template <typename RangeT>
class MemoryOpGenericAdaptor : public detail::MemoryOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MemoryOpGenericAdaptorBase;
public:
  MemoryOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MemoryOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : MemoryOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MemoryOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MemoryOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MemoryOpGenericAdaptor(RangeT values, const MemoryOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MemoryOp, typename = std::enable_if_t<std::is_same_v<LateInst, MemoryOp>>>
  MemoryOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class MemoryOpAdaptor : public MemoryOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MemoryOpGenericAdaptor::MemoryOpGenericAdaptor;
  MemoryOpAdaptor(MemoryOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MemoryOp : public ::mlir::Op<MemoryOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MemoryOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MemoryOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<MemoryOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<MemoryOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<MemoryOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<MemoryOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<MemoryOp>::direction;
  using ::circt::calyx::CellInterface::Trait<MemoryOp>::portName;
  using ::circt::calyx::CellInterface::Trait<MemoryOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<MemoryOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<MemoryOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<MemoryOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<MemoryOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<MemoryOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<MemoryOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("addrSizes"), ::llvm::StringRef("sizes"), ::llvm::StringRef("sym_name"), ::llvm::StringRef("width")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAddrSizesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAddrSizesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getSizesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getSizesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getWidthAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getWidthAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("calyx.memory");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getResults() {
    return getODSResults(0);
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
  ::mlir::IntegerAttr getWidthAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().width);
  }

  uint64_t getWidth();
  ::mlir::ArrayAttr getSizesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().sizes);
  }

  ::mlir::ArrayAttr getSizes();
  ::mlir::ArrayAttr getAddrSizesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().addrSizes);
  }

  ::mlir::ArrayAttr getAddrSizes();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  void setWidthAttr(::mlir::IntegerAttr attr) {
    getProperties().width = attr;
  }

  void setWidth(uint64_t attrValue);
  void setSizesAttr(::mlir::ArrayAttr attr) {
    getProperties().sizes = attr;
  }

  void setAddrSizesAttr(::mlir::ArrayAttr attr) {
    getProperties().addrSizes = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, int64_t width, ArrayRef<int64_t> sizes, ArrayRef<int64_t> addrSizes);
  static MemoryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, int64_t width, ArrayRef<int64_t> sizes, ArrayRef<int64_t> addrSizes);
  static MemoryOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, int64_t width, ArrayRef<int64_t> sizes, ArrayRef<int64_t> addrSizes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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
  size_t getNumDimensions() { return getAddrSizes().size(); }

  ValueRange addrPorts() { return getResults().take_front(getNumDimensions()); }
  Value addrPort(size_t i) {
    assert(i < getNumDimensions() && "index greater than number of memory address ports.");
    return getResults()[i];
  }
  Value writeData() { return getResult(getNumDimensions()); }
  Value writeEn()   { return getResult(getNumDimensions() + 1); }
  Value clk()       { return getResult(getNumDimensions() + 2); }
  Value readData()  { return getResult(getNumDimensions() + 3); }
  Value done()      { return getResult(getNumDimensions() + 4); }
};

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::MemoryOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::MemoryOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::MulFOpIEEE754 declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MulFOpIEEE754GenericAdaptorBase {
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
  MulFOpIEEE754GenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.ieee754.mul", odsAttrs.getContext());
  }

  MulFOpIEEE754GenericAdaptorBase(MulFOpIEEE754 op);

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
class MulFOpIEEE754GenericAdaptor : public detail::MulFOpIEEE754GenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MulFOpIEEE754GenericAdaptorBase;
public:
  MulFOpIEEE754GenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MulFOpIEEE754GenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : MulFOpIEEE754GenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MulFOpIEEE754GenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MulFOpIEEE754GenericAdaptor(values, attrs, Properties{}, {}) {}

  MulFOpIEEE754GenericAdaptor(RangeT values, const MulFOpIEEE754GenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MulFOpIEEE754, typename = std::enable_if_t<std::is_same_v<LateInst, MulFOpIEEE754>>>
  MulFOpIEEE754GenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class MulFOpIEEE754Adaptor : public MulFOpIEEE754GenericAdaptor<::mlir::ValueRange> {
public:
  using MulFOpIEEE754GenericAdaptor::MulFOpIEEE754GenericAdaptor;
  MulFOpIEEE754Adaptor(MulFOpIEEE754 op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MulFOpIEEE754 : public ::mlir::Op<MulFOpIEEE754, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<10>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::FloatingPointOpInterface::Trait, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MulFOpIEEE754Adaptor;
  template <typename RangeT>
  using GenericAdaptor = MulFOpIEEE754GenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<MulFOpIEEE754>::instanceName;
  using ::circt::calyx::CellInterface::Trait<MulFOpIEEE754>::portIndex;
  using ::circt::calyx::CellInterface::Trait<MulFOpIEEE754>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<MulFOpIEEE754>::portInfo;
  using ::circt::calyx::CellInterface::Trait<MulFOpIEEE754>::direction;
  using ::circt::calyx::CellInterface::Trait<MulFOpIEEE754>::portName;
  using ::circt::calyx::CellInterface::Trait<MulFOpIEEE754>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<MulFOpIEEE754>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<MulFOpIEEE754>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<MulFOpIEEE754>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<MulFOpIEEE754>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<MulFOpIEEE754>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<MulFOpIEEE754>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.ieee754.mul");
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

  ::mlir::TypedValue<::mlir::IntegerType> getClk() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getReset() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getGo() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(2).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getControl() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(3).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getLeft() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(4).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getRight() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(5).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getRoundingMode() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(6).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(7).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getExceptionalFlags() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(8).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getDone() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(9).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static MulFOpIEEE754 create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static MulFOpIEEE754 create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static FloatingPointStandard getFloatingPointStandard();
  static std::string getCalyxLibraryName();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::MulFOpIEEE754)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::MulFOpIEEE754GenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::MultPipeLibOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MultPipeLibOpGenericAdaptorBase {
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
  MultPipeLibOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.std_mult_pipe", odsAttrs.getContext());
  }

  MultPipeLibOpGenericAdaptorBase(MultPipeLibOp op);

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
class MultPipeLibOpGenericAdaptor : public detail::MultPipeLibOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MultPipeLibOpGenericAdaptorBase;
public:
  MultPipeLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MultPipeLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : MultPipeLibOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MultPipeLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MultPipeLibOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MultPipeLibOpGenericAdaptor(RangeT values, const MultPipeLibOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MultPipeLibOp, typename = std::enable_if_t<std::is_same_v<LateInst, MultPipeLibOp>>>
  MultPipeLibOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class MultPipeLibOpAdaptor : public MultPipeLibOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MultPipeLibOpGenericAdaptor::MultPipeLibOpGenericAdaptor;
  MultPipeLibOpAdaptor(MultPipeLibOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MultPipeLibOp : public ::mlir::Op<MultPipeLibOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<7>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MultPipeLibOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MultPipeLibOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<MultPipeLibOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<MultPipeLibOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<MultPipeLibOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<MultPipeLibOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<MultPipeLibOp>::direction;
  using ::circt::calyx::CellInterface::Trait<MultPipeLibOp>::portName;
  using ::circt::calyx::CellInterface::Trait<MultPipeLibOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<MultPipeLibOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<MultPipeLibOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<MultPipeLibOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<MultPipeLibOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<MultPipeLibOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<MultPipeLibOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.std_mult_pipe");
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

  ::mlir::TypedValue<::mlir::IntegerType> getClk() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getReset() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getGo() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(2).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getLeft() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(3).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getRight() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(4).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(5).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getDone() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(6).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static MultPipeLibOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static MultPipeLibOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::MultPipeLibOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::MultPipeLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::MuxLibOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MuxLibOpGenericAdaptorBase {
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
  MuxLibOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.std_mux", odsAttrs.getContext());
  }

  MuxLibOpGenericAdaptorBase(MuxLibOp op);

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
class MuxLibOpGenericAdaptor : public detail::MuxLibOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MuxLibOpGenericAdaptorBase;
public:
  MuxLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MuxLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : MuxLibOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MuxLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MuxLibOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MuxLibOpGenericAdaptor(RangeT values, const MuxLibOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MuxLibOp, typename = std::enable_if_t<std::is_same_v<LateInst, MuxLibOp>>>
  MuxLibOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class MuxLibOpAdaptor : public MuxLibOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MuxLibOpGenericAdaptor::MuxLibOpGenericAdaptor;
  MuxLibOpAdaptor(MuxLibOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MuxLibOp : public ::mlir::Op<MuxLibOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<4>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::Combinational, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MuxLibOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MuxLibOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<MuxLibOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<MuxLibOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<MuxLibOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<MuxLibOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<MuxLibOp>::direction;
  using ::circt::calyx::CellInterface::Trait<MuxLibOp>::portName;
  using ::circt::calyx::CellInterface::Trait<MuxLibOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<MuxLibOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<MuxLibOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<MuxLibOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<MuxLibOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<MuxLibOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<MuxLibOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.std_mux");
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

  ::mlir::TypedValue<::mlir::IntegerType> getCond() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getTru() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getFal() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(2).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(3).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static MuxLibOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static MuxLibOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::MuxLibOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::MuxLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::NeqLibOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class NeqLibOpGenericAdaptorBase {
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
  NeqLibOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.std_neq", odsAttrs.getContext());
  }

  NeqLibOpGenericAdaptorBase(NeqLibOp op);

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
class NeqLibOpGenericAdaptor : public detail::NeqLibOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::NeqLibOpGenericAdaptorBase;
public:
  NeqLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  NeqLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : NeqLibOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  NeqLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : NeqLibOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  NeqLibOpGenericAdaptor(RangeT values, const NeqLibOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = NeqLibOp, typename = std::enable_if_t<std::is_same_v<LateInst, NeqLibOp>>>
  NeqLibOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class NeqLibOpAdaptor : public NeqLibOpGenericAdaptor<::mlir::ValueRange> {
public:
  using NeqLibOpGenericAdaptor::NeqLibOpGenericAdaptor;
  NeqLibOpAdaptor(NeqLibOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class NeqLibOp : public ::mlir::Op<NeqLibOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<3>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::Combinational, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = NeqLibOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = NeqLibOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<NeqLibOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<NeqLibOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<NeqLibOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<NeqLibOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<NeqLibOp>::direction;
  using ::circt::calyx::CellInterface::Trait<NeqLibOp>::portName;
  using ::circt::calyx::CellInterface::Trait<NeqLibOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<NeqLibOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<NeqLibOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<NeqLibOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<NeqLibOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<NeqLibOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<NeqLibOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.std_neq");
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

  ::mlir::TypedValue<::mlir::Type> getLeft() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getRight() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(2).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static NeqLibOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static NeqLibOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::NeqLibOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::NeqLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::NotLibOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class NotLibOpGenericAdaptorBase {
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
  NotLibOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.std_not", odsAttrs.getContext());
  }

  NotLibOpGenericAdaptorBase(NotLibOp op);

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
class NotLibOpGenericAdaptor : public detail::NotLibOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::NotLibOpGenericAdaptorBase;
public:
  NotLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  NotLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : NotLibOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  NotLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : NotLibOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  NotLibOpGenericAdaptor(RangeT values, const NotLibOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = NotLibOp, typename = std::enable_if_t<std::is_same_v<LateInst, NotLibOp>>>
  NotLibOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class NotLibOpAdaptor : public NotLibOpGenericAdaptor<::mlir::ValueRange> {
public:
  using NotLibOpGenericAdaptor::NotLibOpGenericAdaptor;
  NotLibOpAdaptor(NotLibOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class NotLibOp : public ::mlir::Op<NotLibOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<2>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::Combinational, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = NotLibOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = NotLibOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<NotLibOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<NotLibOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<NotLibOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<NotLibOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<NotLibOp>::direction;
  using ::circt::calyx::CellInterface::Trait<NotLibOp>::portName;
  using ::circt::calyx::CellInterface::Trait<NotLibOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<NotLibOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<NotLibOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<NotLibOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<NotLibOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<NotLibOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<NotLibOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.std_not");
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

  ::mlir::TypedValue<::mlir::IntegerType> getIn() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(1).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static NotLibOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static NotLibOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::NotLibOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::NotLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::OrLibOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class OrLibOpGenericAdaptorBase {
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
  OrLibOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.std_or", odsAttrs.getContext());
  }

  OrLibOpGenericAdaptorBase(OrLibOp op);

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
class OrLibOpGenericAdaptor : public detail::OrLibOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::OrLibOpGenericAdaptorBase;
public:
  OrLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  OrLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : OrLibOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  OrLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : OrLibOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  OrLibOpGenericAdaptor(RangeT values, const OrLibOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = OrLibOp, typename = std::enable_if_t<std::is_same_v<LateInst, OrLibOp>>>
  OrLibOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class OrLibOpAdaptor : public OrLibOpGenericAdaptor<::mlir::ValueRange> {
public:
  using OrLibOpGenericAdaptor::OrLibOpGenericAdaptor;
  OrLibOpAdaptor(OrLibOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class OrLibOp : public ::mlir::Op<OrLibOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<3>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::Combinational, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = OrLibOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = OrLibOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<OrLibOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<OrLibOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<OrLibOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<OrLibOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<OrLibOp>::direction;
  using ::circt::calyx::CellInterface::Trait<OrLibOp>::portName;
  using ::circt::calyx::CellInterface::Trait<OrLibOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<OrLibOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<OrLibOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<OrLibOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<OrLibOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<OrLibOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<OrLibOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.std_or");
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

  ::mlir::TypedValue<::mlir::Type> getLeft() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getRight() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(2).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static OrLibOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static OrLibOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::OrLibOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::OrLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::PadLibOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PadLibOpGenericAdaptorBase {
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
  PadLibOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.std_pad", odsAttrs.getContext());
  }

  PadLibOpGenericAdaptorBase(PadLibOp op);

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
class PadLibOpGenericAdaptor : public detail::PadLibOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PadLibOpGenericAdaptorBase;
public:
  PadLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PadLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : PadLibOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PadLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : PadLibOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PadLibOpGenericAdaptor(RangeT values, const PadLibOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PadLibOp, typename = std::enable_if_t<std::is_same_v<LateInst, PadLibOp>>>
  PadLibOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class PadLibOpAdaptor : public PadLibOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PadLibOpGenericAdaptor::PadLibOpGenericAdaptor;
  PadLibOpAdaptor(PadLibOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PadLibOp : public ::mlir::Op<PadLibOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<2>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::Combinational, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PadLibOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PadLibOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<PadLibOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<PadLibOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<PadLibOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<PadLibOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<PadLibOp>::direction;
  using ::circt::calyx::CellInterface::Trait<PadLibOp>::portName;
  using ::circt::calyx::CellInterface::Trait<PadLibOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<PadLibOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<PadLibOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<PadLibOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<PadLibOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<PadLibOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<PadLibOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.std_pad");
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

  ::mlir::TypedValue<::mlir::IntegerType> getIn() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(1).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static PadLibOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static PadLibOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::PadLibOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::PadLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::ParOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ParOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ParOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.par", odsAttrs.getContext());
  }

  ParOpGenericAdaptorBase(ParOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class ParOpGenericAdaptor : public detail::ParOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ParOpGenericAdaptorBase;
public:
  ParOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ParOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ParOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ParOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ParOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ParOpGenericAdaptor(RangeT values, const ParOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ParOp, typename = std::enable_if_t<std::is_same_v<LateInst, ParOp>>>
  ParOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ParOpAdaptor : public ParOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ParOpGenericAdaptor::ParOpGenericAdaptor;
  ParOpAdaptor(ParOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ParOp : public ::mlir::Op<ParOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::OpInvariants, ::circt::calyx::ControlLike> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ParOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ParOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("calyx.par");
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static ParOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static ParOp create(::mlir::ImplicitLocOpBuilder &builder);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  /// Returns the body of a Calyx container.
  Block *getBodyBlock() {
    Region* region = &getOperation()->getRegion(0);
    assert(region->hasOneBlock() && "The body should have one Block.");
    return &region->front();
  }
};

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::ParOp)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::PrimitiveOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PrimitiveOpGenericAdaptorBase {
public:
  struct Properties {
    using parametersTy = ::mlir::ArrayAttr;
    parametersTy parameters;

    auto getParameters() const {
      auto &propStorage = this->parameters;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setParameters(const ::mlir::ArrayAttr &propValue) {
      this->parameters = propValue;
    }
    using primitiveNameTy = ::mlir::FlatSymbolRefAttr;
    primitiveNameTy primitiveName;

    auto getPrimitiveName() const {
      auto &propStorage = this->primitiveName;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setPrimitiveName(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->primitiveName = propValue;
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
        rhs.parameters == this->parameters &&
        rhs.primitiveName == this->primitiveName &&
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
  PrimitiveOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.primitive", odsAttrs.getContext());
  }

  PrimitiveOpGenericAdaptorBase(PrimitiveOp op);

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
  ::mlir::ArrayAttr getParametersAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().parameters);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getParameters();
  ::mlir::FlatSymbolRefAttr getPrimitiveNameAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().primitiveName);
    return attr;
  }

  ::llvm::StringRef getPrimitiveName();
};

} // namespace detail
template <typename RangeT>
class PrimitiveOpGenericAdaptor : public detail::PrimitiveOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PrimitiveOpGenericAdaptorBase;
public:
  PrimitiveOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PrimitiveOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : PrimitiveOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PrimitiveOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : PrimitiveOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PrimitiveOpGenericAdaptor(RangeT values, const PrimitiveOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PrimitiveOp, typename = std::enable_if_t<std::is_same_v<LateInst, PrimitiveOp>>>
  PrimitiveOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class PrimitiveOpAdaptor : public PrimitiveOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PrimitiveOpGenericAdaptor::PrimitiveOpGenericAdaptor;
  PrimitiveOpAdaptor(PrimitiveOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PrimitiveOp : public ::mlir::Op<PrimitiveOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PrimitiveOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PrimitiveOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<PrimitiveOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<PrimitiveOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<PrimitiveOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<PrimitiveOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<PrimitiveOp>::direction;
  using ::circt::calyx::CellInterface::Trait<PrimitiveOp>::portName;
  using ::circt::calyx::CellInterface::Trait<PrimitiveOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<PrimitiveOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<PrimitiveOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<PrimitiveOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<PrimitiveOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<PrimitiveOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<PrimitiveOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("parameters"), ::llvm::StringRef("primitiveName"), ::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getParametersAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getParametersAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getPrimitiveNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getPrimitiveNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("calyx.primitive");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getResults() {
    return getODSResults(0);
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
  ::mlir::ArrayAttr getParametersAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().parameters);
  }

  ::std::optional< ::mlir::ArrayAttr > getParameters();
  ::mlir::FlatSymbolRefAttr getPrimitiveNameAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().primitiveName);
  }

  ::llvm::StringRef getPrimitiveName();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  void setParametersAttr(::mlir::ArrayAttr attr) {
    getProperties().parameters = attr;
  }

  void setPrimitiveNameAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().primitiveName = attr;
  }

  void setPrimitiveName(::llvm::StringRef attrValue);
  ::mlir::Attribute removeParametersAttr() {
      auto attr = getProperties().parameters;
      getProperties().parameters = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::StringAttr sym_name, /*optional*/::mlir::ArrayAttr parameters, ::mlir::FlatSymbolRefAttr primitiveName);
  static PrimitiveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::StringAttr sym_name, /*optional*/::mlir::ArrayAttr parameters, ::mlir::FlatSymbolRefAttr primitiveName);
  static PrimitiveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::StringAttr sym_name, /*optional*/::mlir::ArrayAttr parameters, ::mlir::FlatSymbolRefAttr primitiveName);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::llvm::StringRef sym_name, /*optional*/::mlir::ArrayAttr parameters, ::llvm::StringRef primitiveName);
  static PrimitiveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::llvm::StringRef sym_name, /*optional*/::mlir::ArrayAttr parameters, ::llvm::StringRef primitiveName);
  static PrimitiveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::llvm::StringRef sym_name, /*optional*/::mlir::ArrayAttr parameters, ::llvm::StringRef primitiveName);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PrimitiveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PrimitiveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PrimitiveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PrimitiveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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
  /// Lookup the component for the symbol. This returns null on
  /// invalid IR.
  hw::HWModuleExternOp getReferencedPrimitive();
};

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::PrimitiveOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::PrimitiveOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::RegisterOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class RegisterOpGenericAdaptorBase {
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
  RegisterOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.register", odsAttrs.getContext());
  }

  RegisterOpGenericAdaptorBase(RegisterOp op);

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
class RegisterOpGenericAdaptor : public detail::RegisterOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::RegisterOpGenericAdaptorBase;
public:
  RegisterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  RegisterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : RegisterOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  RegisterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : RegisterOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  RegisterOpGenericAdaptor(RangeT values, const RegisterOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = RegisterOp, typename = std::enable_if_t<std::is_same_v<LateInst, RegisterOp>>>
  RegisterOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class RegisterOpAdaptor : public RegisterOpGenericAdaptor<::mlir::ValueRange> {
public:
  using RegisterOpGenericAdaptor::RegisterOpGenericAdaptor;
  RegisterOpAdaptor(RegisterOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class RegisterOp : public ::mlir::Op<RegisterOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<6>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = RegisterOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = RegisterOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<RegisterOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<RegisterOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<RegisterOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<RegisterOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<RegisterOp>::direction;
  using ::circt::calyx::CellInterface::Trait<RegisterOp>::portName;
  using ::circt::calyx::CellInterface::Trait<RegisterOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<RegisterOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<RegisterOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<RegisterOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<RegisterOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<RegisterOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<RegisterOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.register");
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

  ::mlir::TypedValue<::mlir::Type> getIn() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getWriteEn() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getClk() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(2).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getReset() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(3).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(4).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getDone() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(5).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, size_t width);
  static RegisterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, size_t width);
  static RegisterOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, size_t width);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, Type type);
  static RegisterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, Type type);
  static RegisterOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, Type type);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::RegisterOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::RegisterOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::RemSPipeLibOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class RemSPipeLibOpGenericAdaptorBase {
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
  RemSPipeLibOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.std_rems_pipe", odsAttrs.getContext());
  }

  RemSPipeLibOpGenericAdaptorBase(RemSPipeLibOp op);

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
class RemSPipeLibOpGenericAdaptor : public detail::RemSPipeLibOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::RemSPipeLibOpGenericAdaptorBase;
public:
  RemSPipeLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  RemSPipeLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : RemSPipeLibOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  RemSPipeLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : RemSPipeLibOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  RemSPipeLibOpGenericAdaptor(RangeT values, const RemSPipeLibOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = RemSPipeLibOp, typename = std::enable_if_t<std::is_same_v<LateInst, RemSPipeLibOp>>>
  RemSPipeLibOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class RemSPipeLibOpAdaptor : public RemSPipeLibOpGenericAdaptor<::mlir::ValueRange> {
public:
  using RemSPipeLibOpGenericAdaptor::RemSPipeLibOpGenericAdaptor;
  RemSPipeLibOpAdaptor(RemSPipeLibOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class RemSPipeLibOp : public ::mlir::Op<RemSPipeLibOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<7>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = RemSPipeLibOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = RemSPipeLibOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<RemSPipeLibOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<RemSPipeLibOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<RemSPipeLibOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<RemSPipeLibOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<RemSPipeLibOp>::direction;
  using ::circt::calyx::CellInterface::Trait<RemSPipeLibOp>::portName;
  using ::circt::calyx::CellInterface::Trait<RemSPipeLibOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<RemSPipeLibOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<RemSPipeLibOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<RemSPipeLibOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<RemSPipeLibOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<RemSPipeLibOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<RemSPipeLibOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.std_rems_pipe");
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

  ::mlir::TypedValue<::mlir::IntegerType> getClk() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getReset() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getGo() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(2).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getLeft() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(3).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getRight() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(4).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(5).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getDone() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(6).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static RemSPipeLibOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static RemSPipeLibOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::RemSPipeLibOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::RemSPipeLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::RemUPipeLibOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class RemUPipeLibOpGenericAdaptorBase {
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
  RemUPipeLibOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.std_remu_pipe", odsAttrs.getContext());
  }

  RemUPipeLibOpGenericAdaptorBase(RemUPipeLibOp op);

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
class RemUPipeLibOpGenericAdaptor : public detail::RemUPipeLibOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::RemUPipeLibOpGenericAdaptorBase;
public:
  RemUPipeLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  RemUPipeLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : RemUPipeLibOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  RemUPipeLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : RemUPipeLibOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  RemUPipeLibOpGenericAdaptor(RangeT values, const RemUPipeLibOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = RemUPipeLibOp, typename = std::enable_if_t<std::is_same_v<LateInst, RemUPipeLibOp>>>
  RemUPipeLibOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class RemUPipeLibOpAdaptor : public RemUPipeLibOpGenericAdaptor<::mlir::ValueRange> {
public:
  using RemUPipeLibOpGenericAdaptor::RemUPipeLibOpGenericAdaptor;
  RemUPipeLibOpAdaptor(RemUPipeLibOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class RemUPipeLibOp : public ::mlir::Op<RemUPipeLibOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<7>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = RemUPipeLibOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = RemUPipeLibOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<RemUPipeLibOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<RemUPipeLibOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<RemUPipeLibOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<RemUPipeLibOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<RemUPipeLibOp>::direction;
  using ::circt::calyx::CellInterface::Trait<RemUPipeLibOp>::portName;
  using ::circt::calyx::CellInterface::Trait<RemUPipeLibOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<RemUPipeLibOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<RemUPipeLibOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<RemUPipeLibOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<RemUPipeLibOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<RemUPipeLibOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<RemUPipeLibOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.std_remu_pipe");
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

  ::mlir::TypedValue<::mlir::IntegerType> getClk() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getReset() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getGo() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(2).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getLeft() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(3).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getRight() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(4).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(5).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getDone() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(6).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static RemUPipeLibOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static RemUPipeLibOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::RemUPipeLibOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::RemUPipeLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::RepeatOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class RepeatOpGenericAdaptorBase {
public:
  struct Properties {
    using countTy = ::mlir::IntegerAttr;
    countTy count;

    auto getCount() const {
      auto &propStorage = this->count;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setCount(const ::mlir::IntegerAttr &propValue) {
      this->count = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.count == this->count &&
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
  RepeatOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.repeat", odsAttrs.getContext());
  }

  RepeatOpGenericAdaptorBase(RepeatOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getCountAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().count);
    return attr;
  }

  uint32_t getCount();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class RepeatOpGenericAdaptor : public detail::RepeatOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::RepeatOpGenericAdaptorBase;
public:
  RepeatOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  RepeatOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : RepeatOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  RepeatOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : RepeatOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  RepeatOpGenericAdaptor(RangeT values, const RepeatOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = RepeatOp, typename = std::enable_if_t<std::is_same_v<LateInst, RepeatOp>>>
  RepeatOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class RepeatOpAdaptor : public RepeatOpGenericAdaptor<::mlir::ValueRange> {
public:
  using RepeatOpGenericAdaptor::RepeatOpGenericAdaptor;
  RepeatOpAdaptor(RepeatOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class RepeatOp : public ::mlir::Op<RepeatOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::ControlLike> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = RepeatOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = RepeatOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("count")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getCountAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getCountAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("calyx.repeat");
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
  ::mlir::IntegerAttr getCountAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().count);
  }

  uint32_t getCount();
  void setCountAttr(::mlir::IntegerAttr attr) {
    getProperties().count = attr;
  }

  void setCount(uint32_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, uint32_t count);
  static RepeatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, uint32_t count);
  static RepeatOp create(::mlir::ImplicitLocOpBuilder &builder, uint32_t count);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
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
  /// Returns the body of a Calyx container.
  Block *getBodyBlock() {
    Region* region = &getOperation()->getRegion(0);
    assert(region->hasOneBlock() && "The body should have one Block.");
    return &region->front();
  }
};

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::RepeatOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::RepeatOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::RshLibOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class RshLibOpGenericAdaptorBase {
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
  RshLibOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.std_rsh", odsAttrs.getContext());
  }

  RshLibOpGenericAdaptorBase(RshLibOp op);

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
class RshLibOpGenericAdaptor : public detail::RshLibOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::RshLibOpGenericAdaptorBase;
public:
  RshLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  RshLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : RshLibOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  RshLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : RshLibOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  RshLibOpGenericAdaptor(RangeT values, const RshLibOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = RshLibOp, typename = std::enable_if_t<std::is_same_v<LateInst, RshLibOp>>>
  RshLibOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class RshLibOpAdaptor : public RshLibOpGenericAdaptor<::mlir::ValueRange> {
public:
  using RshLibOpGenericAdaptor::RshLibOpGenericAdaptor;
  RshLibOpAdaptor(RshLibOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class RshLibOp : public ::mlir::Op<RshLibOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<3>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::Combinational, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = RshLibOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = RshLibOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<RshLibOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<RshLibOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<RshLibOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<RshLibOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<RshLibOp>::direction;
  using ::circt::calyx::CellInterface::Trait<RshLibOp>::portName;
  using ::circt::calyx::CellInterface::Trait<RshLibOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<RshLibOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<RshLibOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<RshLibOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<RshLibOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<RshLibOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<RshLibOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.std_rsh");
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

  ::mlir::TypedValue<::mlir::Type> getLeft() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getRight() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(2).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static RshLibOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static RshLibOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::RshLibOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::RshLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::SeqLibOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SeqLibOpGenericAdaptorBase {
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
  SeqLibOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.std_seq", odsAttrs.getContext());
  }

  SeqLibOpGenericAdaptorBase(SeqLibOp op);

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
class SeqLibOpGenericAdaptor : public detail::SeqLibOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SeqLibOpGenericAdaptorBase;
public:
  SeqLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SeqLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SeqLibOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SeqLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SeqLibOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SeqLibOpGenericAdaptor(RangeT values, const SeqLibOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SeqLibOp, typename = std::enable_if_t<std::is_same_v<LateInst, SeqLibOp>>>
  SeqLibOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SeqLibOpAdaptor : public SeqLibOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SeqLibOpGenericAdaptor::SeqLibOpGenericAdaptor;
  SeqLibOpAdaptor(SeqLibOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SeqLibOp : public ::mlir::Op<SeqLibOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<3>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::Combinational, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SeqLibOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SeqLibOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<SeqLibOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<SeqLibOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<SeqLibOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<SeqLibOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<SeqLibOp>::direction;
  using ::circt::calyx::CellInterface::Trait<SeqLibOp>::portName;
  using ::circt::calyx::CellInterface::Trait<SeqLibOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<SeqLibOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<SeqLibOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<SeqLibOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<SeqLibOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<SeqLibOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<SeqLibOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.std_seq");
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

  ::mlir::TypedValue<::mlir::Type> getLeft() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getRight() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(2).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static SeqLibOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static SeqLibOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::SeqLibOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::SeqLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::SeqMemoryOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SeqMemoryOpGenericAdaptorBase {
public:
  struct Properties {
    using addrSizesTy = ::mlir::ArrayAttr;
    addrSizesTy addrSizes;

    auto getAddrSizes() const {
      auto &propStorage = this->addrSizes;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setAddrSizes(const ::mlir::ArrayAttr &propValue) {
      this->addrSizes = propValue;
    }
    using sizesTy = ::mlir::ArrayAttr;
    sizesTy sizes;

    auto getSizes() const {
      auto &propStorage = this->sizes;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setSizes(const ::mlir::ArrayAttr &propValue) {
      this->sizes = propValue;
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
    using widthTy = ::mlir::IntegerAttr;
    widthTy width;

    auto getWidth() const {
      auto &propStorage = this->width;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setWidth(const ::mlir::IntegerAttr &propValue) {
      this->width = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.addrSizes == this->addrSizes &&
        rhs.sizes == this->sizes &&
        rhs.sym_name == this->sym_name &&
        rhs.width == this->width &&
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
  SeqMemoryOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.seq_mem", odsAttrs.getContext());
  }

  SeqMemoryOpGenericAdaptorBase(SeqMemoryOp op);

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
  ::mlir::IntegerAttr getWidthAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().width);
    return attr;
  }

  uint64_t getWidth();
  ::mlir::ArrayAttr getSizesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().sizes);
    return attr;
  }

  ::mlir::ArrayAttr getSizes();
  ::mlir::ArrayAttr getAddrSizesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().addrSizes);
    return attr;
  }

  ::mlir::ArrayAttr getAddrSizes();
};

} // namespace detail
template <typename RangeT>
class SeqMemoryOpGenericAdaptor : public detail::SeqMemoryOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SeqMemoryOpGenericAdaptorBase;
public:
  SeqMemoryOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SeqMemoryOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SeqMemoryOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SeqMemoryOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SeqMemoryOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SeqMemoryOpGenericAdaptor(RangeT values, const SeqMemoryOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SeqMemoryOp, typename = std::enable_if_t<std::is_same_v<LateInst, SeqMemoryOp>>>
  SeqMemoryOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SeqMemoryOpAdaptor : public SeqMemoryOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SeqMemoryOpGenericAdaptor::SeqMemoryOpGenericAdaptor;
  SeqMemoryOpAdaptor(SeqMemoryOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SeqMemoryOp : public ::mlir::Op<SeqMemoryOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SeqMemoryOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SeqMemoryOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<SeqMemoryOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<SeqMemoryOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<SeqMemoryOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<SeqMemoryOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<SeqMemoryOp>::direction;
  using ::circt::calyx::CellInterface::Trait<SeqMemoryOp>::portName;
  using ::circt::calyx::CellInterface::Trait<SeqMemoryOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<SeqMemoryOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<SeqMemoryOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<SeqMemoryOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<SeqMemoryOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<SeqMemoryOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<SeqMemoryOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("addrSizes"), ::llvm::StringRef("sizes"), ::llvm::StringRef("sym_name"), ::llvm::StringRef("width")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAddrSizesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAddrSizesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getSizesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getSizesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getWidthAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getWidthAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("calyx.seq_mem");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getResults() {
    return getODSResults(0);
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
  ::mlir::IntegerAttr getWidthAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().width);
  }

  uint64_t getWidth();
  ::mlir::ArrayAttr getSizesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().sizes);
  }

  ::mlir::ArrayAttr getSizes();
  ::mlir::ArrayAttr getAddrSizesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().addrSizes);
  }

  ::mlir::ArrayAttr getAddrSizes();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  void setWidthAttr(::mlir::IntegerAttr attr) {
    getProperties().width = attr;
  }

  void setWidth(uint64_t attrValue);
  void setSizesAttr(::mlir::ArrayAttr attr) {
    getProperties().sizes = attr;
  }

  void setAddrSizesAttr(::mlir::ArrayAttr attr) {
    getProperties().addrSizes = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, int64_t width, ArrayRef<int64_t> sizes, ArrayRef<int64_t> addrSizes);
  static SeqMemoryOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, int64_t width, ArrayRef<int64_t> sizes, ArrayRef<int64_t> addrSizes);
  static SeqMemoryOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, int64_t width, ArrayRef<int64_t> sizes, ArrayRef<int64_t> addrSizes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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
  size_t getNumDimensions() { return getAddrSizes().size(); }

  ValueRange addrPorts() { return getResults().take_front(getNumDimensions()); }
  Value addrPort(size_t i) {
    assert(i < getNumDimensions() && "index greater than number of memory address ports.");
    return getResults()[i];
  }
  Value clk() { return getResult(getNumDimensions()); }
  Value reset()   { return getResult(getNumDimensions() + 1); }
  Value contentEn()      { return getResult(getNumDimensions() + 2); }
  Value writeEn()       { return getResult(getNumDimensions() + 3); }
  Value writeData()  { return getResult(getNumDimensions() + 4); }
  Value readData()  { return getResult(getNumDimensions() + 5); }
  Value done()      { return getResult(getNumDimensions() + 6); }
};

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::SeqMemoryOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::SeqMemoryOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::SeqOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SeqOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SeqOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.seq", odsAttrs.getContext());
  }

  SeqOpGenericAdaptorBase(SeqOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class SeqOpGenericAdaptor : public detail::SeqOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SeqOpGenericAdaptorBase;
public:
  SeqOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SeqOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SeqOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SeqOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SeqOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SeqOpGenericAdaptor(RangeT values, const SeqOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SeqOp, typename = std::enable_if_t<std::is_same_v<LateInst, SeqOp>>>
  SeqOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SeqOpAdaptor : public SeqOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SeqOpGenericAdaptor::SeqOpGenericAdaptor;
  SeqOpAdaptor(SeqOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SeqOp : public ::mlir::Op<SeqOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::OpInvariants, ::circt::calyx::ControlLike> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SeqOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SeqOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("calyx.seq");
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static SeqOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static SeqOp create(::mlir::ImplicitLocOpBuilder &builder);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  /// Returns the body of a Calyx container.
  Block *getBodyBlock() {
    Region* region = &getOperation()->getRegion(0);
    assert(region->hasOneBlock() && "The body should have one Block.");
    return &region->front();
  }
};

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::SeqOp)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::SgeLibOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SgeLibOpGenericAdaptorBase {
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
  SgeLibOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.std_sge", odsAttrs.getContext());
  }

  SgeLibOpGenericAdaptorBase(SgeLibOp op);

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
class SgeLibOpGenericAdaptor : public detail::SgeLibOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SgeLibOpGenericAdaptorBase;
public:
  SgeLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SgeLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SgeLibOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SgeLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SgeLibOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SgeLibOpGenericAdaptor(RangeT values, const SgeLibOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SgeLibOp, typename = std::enable_if_t<std::is_same_v<LateInst, SgeLibOp>>>
  SgeLibOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SgeLibOpAdaptor : public SgeLibOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SgeLibOpGenericAdaptor::SgeLibOpGenericAdaptor;
  SgeLibOpAdaptor(SgeLibOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SgeLibOp : public ::mlir::Op<SgeLibOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<3>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::Combinational, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SgeLibOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SgeLibOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<SgeLibOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<SgeLibOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<SgeLibOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<SgeLibOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<SgeLibOp>::direction;
  using ::circt::calyx::CellInterface::Trait<SgeLibOp>::portName;
  using ::circt::calyx::CellInterface::Trait<SgeLibOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<SgeLibOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<SgeLibOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<SgeLibOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<SgeLibOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<SgeLibOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<SgeLibOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.std_sge");
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

  ::mlir::TypedValue<::mlir::Type> getLeft() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getRight() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(2).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static SgeLibOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static SgeLibOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::SgeLibOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::SgeLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::SgtLibOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SgtLibOpGenericAdaptorBase {
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
  SgtLibOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.std_sgt", odsAttrs.getContext());
  }

  SgtLibOpGenericAdaptorBase(SgtLibOp op);

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
class SgtLibOpGenericAdaptor : public detail::SgtLibOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SgtLibOpGenericAdaptorBase;
public:
  SgtLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SgtLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SgtLibOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SgtLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SgtLibOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SgtLibOpGenericAdaptor(RangeT values, const SgtLibOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SgtLibOp, typename = std::enable_if_t<std::is_same_v<LateInst, SgtLibOp>>>
  SgtLibOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SgtLibOpAdaptor : public SgtLibOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SgtLibOpGenericAdaptor::SgtLibOpGenericAdaptor;
  SgtLibOpAdaptor(SgtLibOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SgtLibOp : public ::mlir::Op<SgtLibOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<3>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::Combinational, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SgtLibOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SgtLibOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<SgtLibOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<SgtLibOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<SgtLibOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<SgtLibOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<SgtLibOp>::direction;
  using ::circt::calyx::CellInterface::Trait<SgtLibOp>::portName;
  using ::circt::calyx::CellInterface::Trait<SgtLibOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<SgtLibOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<SgtLibOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<SgtLibOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<SgtLibOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<SgtLibOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<SgtLibOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.std_sgt");
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

  ::mlir::TypedValue<::mlir::Type> getLeft() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getRight() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(2).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static SgtLibOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static SgtLibOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::SgtLibOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::SgtLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::ShruLibOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ShruLibOpGenericAdaptorBase {
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
  ShruLibOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.std_shru", odsAttrs.getContext());
  }

  ShruLibOpGenericAdaptorBase(ShruLibOp op);

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
class ShruLibOpGenericAdaptor : public detail::ShruLibOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ShruLibOpGenericAdaptorBase;
public:
  ShruLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ShruLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ShruLibOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ShruLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ShruLibOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ShruLibOpGenericAdaptor(RangeT values, const ShruLibOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ShruLibOp, typename = std::enable_if_t<std::is_same_v<LateInst, ShruLibOp>>>
  ShruLibOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ShruLibOpAdaptor : public ShruLibOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ShruLibOpGenericAdaptor::ShruLibOpGenericAdaptor;
  ShruLibOpAdaptor(ShruLibOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ShruLibOp : public ::mlir::Op<ShruLibOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<3>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::Combinational, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ShruLibOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ShruLibOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<ShruLibOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<ShruLibOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<ShruLibOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<ShruLibOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<ShruLibOp>::direction;
  using ::circt::calyx::CellInterface::Trait<ShruLibOp>::portName;
  using ::circt::calyx::CellInterface::Trait<ShruLibOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<ShruLibOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<ShruLibOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<ShruLibOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<ShruLibOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<ShruLibOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<ShruLibOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.std_shru");
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

  ::mlir::TypedValue<::mlir::Type> getLeft() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getRight() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(2).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static ShruLibOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static ShruLibOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::ShruLibOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::ShruLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::SleLibOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SleLibOpGenericAdaptorBase {
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
  SleLibOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.std_sle", odsAttrs.getContext());
  }

  SleLibOpGenericAdaptorBase(SleLibOp op);

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
class SleLibOpGenericAdaptor : public detail::SleLibOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SleLibOpGenericAdaptorBase;
public:
  SleLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SleLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SleLibOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SleLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SleLibOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SleLibOpGenericAdaptor(RangeT values, const SleLibOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SleLibOp, typename = std::enable_if_t<std::is_same_v<LateInst, SleLibOp>>>
  SleLibOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SleLibOpAdaptor : public SleLibOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SleLibOpGenericAdaptor::SleLibOpGenericAdaptor;
  SleLibOpAdaptor(SleLibOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SleLibOp : public ::mlir::Op<SleLibOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<3>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::Combinational, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SleLibOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SleLibOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<SleLibOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<SleLibOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<SleLibOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<SleLibOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<SleLibOp>::direction;
  using ::circt::calyx::CellInterface::Trait<SleLibOp>::portName;
  using ::circt::calyx::CellInterface::Trait<SleLibOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<SleLibOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<SleLibOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<SleLibOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<SleLibOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<SleLibOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<SleLibOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.std_sle");
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

  ::mlir::TypedValue<::mlir::Type> getLeft() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getRight() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(2).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static SleLibOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static SleLibOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::SleLibOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::SleLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::SliceLibOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SliceLibOpGenericAdaptorBase {
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
  SliceLibOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.std_slice", odsAttrs.getContext());
  }

  SliceLibOpGenericAdaptorBase(SliceLibOp op);

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
class SliceLibOpGenericAdaptor : public detail::SliceLibOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SliceLibOpGenericAdaptorBase;
public:
  SliceLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SliceLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SliceLibOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SliceLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SliceLibOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SliceLibOpGenericAdaptor(RangeT values, const SliceLibOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SliceLibOp, typename = std::enable_if_t<std::is_same_v<LateInst, SliceLibOp>>>
  SliceLibOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SliceLibOpAdaptor : public SliceLibOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SliceLibOpGenericAdaptor::SliceLibOpGenericAdaptor;
  SliceLibOpAdaptor(SliceLibOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SliceLibOp : public ::mlir::Op<SliceLibOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<2>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::Combinational, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SliceLibOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SliceLibOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<SliceLibOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<SliceLibOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<SliceLibOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<SliceLibOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<SliceLibOp>::direction;
  using ::circt::calyx::CellInterface::Trait<SliceLibOp>::portName;
  using ::circt::calyx::CellInterface::Trait<SliceLibOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<SliceLibOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<SliceLibOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<SliceLibOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<SliceLibOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<SliceLibOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<SliceLibOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.std_slice");
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

  ::mlir::TypedValue<::mlir::IntegerType> getIn() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(1).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static SliceLibOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static SliceLibOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::SliceLibOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::SliceLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::SltLibOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SltLibOpGenericAdaptorBase {
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
  SltLibOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.std_slt", odsAttrs.getContext());
  }

  SltLibOpGenericAdaptorBase(SltLibOp op);

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
class SltLibOpGenericAdaptor : public detail::SltLibOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SltLibOpGenericAdaptorBase;
public:
  SltLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SltLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SltLibOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SltLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SltLibOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SltLibOpGenericAdaptor(RangeT values, const SltLibOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SltLibOp, typename = std::enable_if_t<std::is_same_v<LateInst, SltLibOp>>>
  SltLibOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SltLibOpAdaptor : public SltLibOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SltLibOpGenericAdaptor::SltLibOpGenericAdaptor;
  SltLibOpAdaptor(SltLibOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SltLibOp : public ::mlir::Op<SltLibOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<3>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::Combinational, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SltLibOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SltLibOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<SltLibOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<SltLibOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<SltLibOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<SltLibOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<SltLibOp>::direction;
  using ::circt::calyx::CellInterface::Trait<SltLibOp>::portName;
  using ::circt::calyx::CellInterface::Trait<SltLibOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<SltLibOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<SltLibOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<SltLibOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<SltLibOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<SltLibOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<SltLibOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.std_slt");
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

  ::mlir::TypedValue<::mlir::Type> getLeft() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getRight() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(2).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static SltLibOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static SltLibOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::SltLibOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::SltLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::SneqLibOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SneqLibOpGenericAdaptorBase {
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
  SneqLibOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.std_sneq", odsAttrs.getContext());
  }

  SneqLibOpGenericAdaptorBase(SneqLibOp op);

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
class SneqLibOpGenericAdaptor : public detail::SneqLibOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SneqLibOpGenericAdaptorBase;
public:
  SneqLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SneqLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SneqLibOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SneqLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SneqLibOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SneqLibOpGenericAdaptor(RangeT values, const SneqLibOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SneqLibOp, typename = std::enable_if_t<std::is_same_v<LateInst, SneqLibOp>>>
  SneqLibOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SneqLibOpAdaptor : public SneqLibOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SneqLibOpGenericAdaptor::SneqLibOpGenericAdaptor;
  SneqLibOpAdaptor(SneqLibOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SneqLibOp : public ::mlir::Op<SneqLibOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<3>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::Combinational, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SneqLibOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SneqLibOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<SneqLibOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<SneqLibOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<SneqLibOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<SneqLibOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<SneqLibOp>::direction;
  using ::circt::calyx::CellInterface::Trait<SneqLibOp>::portName;
  using ::circt::calyx::CellInterface::Trait<SneqLibOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<SneqLibOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<SneqLibOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<SneqLibOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<SneqLibOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<SneqLibOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<SneqLibOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.std_sneq");
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

  ::mlir::TypedValue<::mlir::Type> getLeft() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getRight() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(2).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static SneqLibOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static SneqLibOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::SneqLibOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::SneqLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::SrshLibOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SrshLibOpGenericAdaptorBase {
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
  SrshLibOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.std_srsh", odsAttrs.getContext());
  }

  SrshLibOpGenericAdaptorBase(SrshLibOp op);

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
class SrshLibOpGenericAdaptor : public detail::SrshLibOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SrshLibOpGenericAdaptorBase;
public:
  SrshLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SrshLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SrshLibOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SrshLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SrshLibOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SrshLibOpGenericAdaptor(RangeT values, const SrshLibOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SrshLibOp, typename = std::enable_if_t<std::is_same_v<LateInst, SrshLibOp>>>
  SrshLibOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SrshLibOpAdaptor : public SrshLibOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SrshLibOpGenericAdaptor::SrshLibOpGenericAdaptor;
  SrshLibOpAdaptor(SrshLibOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SrshLibOp : public ::mlir::Op<SrshLibOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<3>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::Combinational, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SrshLibOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SrshLibOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<SrshLibOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<SrshLibOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<SrshLibOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<SrshLibOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<SrshLibOp>::direction;
  using ::circt::calyx::CellInterface::Trait<SrshLibOp>::portName;
  using ::circt::calyx::CellInterface::Trait<SrshLibOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<SrshLibOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<SrshLibOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<SrshLibOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<SrshLibOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<SrshLibOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<SrshLibOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.std_srsh");
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

  ::mlir::TypedValue<::mlir::Type> getLeft() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getRight() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(2).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static SrshLibOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static SrshLibOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::SrshLibOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::SrshLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::StaticGroupOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class StaticGroupOpGenericAdaptorBase {
public:
  struct Properties {
    using latencyTy = ::mlir::IntegerAttr;
    latencyTy latency;

    auto getLatency() const {
      auto &propStorage = this->latency;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setLatency(const ::mlir::IntegerAttr &propValue) {
      this->latency = propValue;
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
        rhs.latency == this->latency &&
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
  StaticGroupOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.static_group", odsAttrs.getContext());
  }

  StaticGroupOpGenericAdaptorBase(StaticGroupOp op);

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
  ::mlir::IntegerAttr getLatencyAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().latency);
    return attr;
  }

  uint64_t getLatency();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class StaticGroupOpGenericAdaptor : public detail::StaticGroupOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::StaticGroupOpGenericAdaptorBase;
public:
  StaticGroupOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  StaticGroupOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : StaticGroupOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  StaticGroupOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : StaticGroupOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  StaticGroupOpGenericAdaptor(RangeT values, const StaticGroupOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = StaticGroupOp, typename = std::enable_if_t<std::is_same_v<LateInst, StaticGroupOp>>>
  StaticGroupOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class StaticGroupOpAdaptor : public StaticGroupOpGenericAdaptor<::mlir::ValueRange> {
public:
  using StaticGroupOpGenericAdaptor::StaticGroupOpGenericAdaptor;
  StaticGroupOpAdaptor(StaticGroupOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class StaticGroupOp : public ::mlir::Op<StaticGroupOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<WiresOp>::Impl, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::GroupInterface::Trait, ::mlir::RegionKindInterface::Trait, ::mlir::SymbolOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = StaticGroupOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = StaticGroupOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("latency"), ::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getLatencyAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getLatencyAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("calyx.static_group");
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
  ::mlir::IntegerAttr getLatencyAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().latency);
  }

  uint64_t getLatency();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  void setLatencyAttr(::mlir::IntegerAttr attr) {
    getProperties().latency = attr;
  }

  void setLatency(uint64_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, uint64_t latency);
  static StaticGroupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, uint64_t latency);
  static StaticGroupOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, uint64_t latency);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringAttr sym_name, uint64_t latency);
  static StaticGroupOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr sym_name, uint64_t latency);
  static StaticGroupOp create(::mlir::ImplicitLocOpBuilder &builder, StringAttr sym_name, uint64_t latency);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  LogicalResult drivesPort(Value port);
  LogicalResult drivesAllPorts(ValueRange ports);
  LogicalResult drivesAnyPort(ValueRange ports);
  LogicalResult readsAnyPort(ValueRange ports);
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
  // Implement RegionKindInterface.
  static RegionKind getRegionKind(unsigned index) { return RegionKind::Graph; }

  /// Returns the GroupGoOp for this group.
  GroupGoOp getGoOp();

  /// Returns the body of a Calyx component.
  Block *getBodyBlock() {
    Region* region = &getOperation()->getRegion(0);
    assert(region->hasOneBlock() && "The body should have one Block.");
    return &region->front();
  }
};

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::StaticGroupOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::StaticGroupOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::StaticIfOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class StaticIfOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  StaticIfOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.static_if", odsAttrs.getContext());
  }

  StaticIfOpGenericAdaptorBase(StaticIfOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::Region &getThenRegion() {
    return *odsRegions[0];
  }

  ::mlir::Region &getElseRegion() {
    return *odsRegions[1];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class StaticIfOpGenericAdaptor : public detail::StaticIfOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::StaticIfOpGenericAdaptorBase;
  static constexpr int odsIndex_cond = 0;
public:
  StaticIfOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  StaticIfOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : StaticIfOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  StaticIfOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : StaticIfOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  StaticIfOpGenericAdaptor(RangeT values, const StaticIfOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = StaticIfOp, typename = std::enable_if_t<std::is_same_v<LateInst, StaticIfOp>>>
  StaticIfOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getCond() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class StaticIfOpAdaptor : public StaticIfOpGenericAdaptor<::mlir::ValueRange> {
public:
  using StaticIfOpGenericAdaptor::StaticIfOpGenericAdaptor;
  StaticIfOpAdaptor(StaticIfOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class StaticIfOp : public ::mlir::Op<StaticIfOp, ::mlir::OpTrait::NRegions<2>::Impl, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::OpInvariants, ::circt::calyx::ControlLike, ::circt::calyx::IfInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = StaticIfOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = StaticIfOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_cond = 0;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::IfInterface::Trait<StaticIfOp>::thenBodyExists;
  using ::circt::calyx::IfInterface::Trait<StaticIfOp>::elseBodyExists;
  using ::circt::calyx::IfInterface::Trait<StaticIfOp>::getThenBody;
  using ::circt::calyx::IfInterface::Trait<StaticIfOp>::getElseBody;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("calyx.static_if");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getCond() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getCondMutable() {
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

  ::mlir::Region &getThenRegion() {
    return (*this)->getRegion(0);
  }

  ::mlir::Region &getElseRegion() {
    return (*this)->getRegion(1);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value cond, bool initializeElseBody = false);
  static StaticIfOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value cond, bool initializeElseBody = false);
  static StaticIfOp create(::mlir::ImplicitLocOpBuilder &builder, Value cond, bool initializeElseBody = false);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  /// Returns the body of a Calyx container.
  Block *getBodyBlock() {
    Region* region = &getOperation()->getRegion(0);
    assert(region->hasOneBlock() && "The body should have one Block.");
    return &region->front();
  }
};

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::StaticIfOp)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::StaticParOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class StaticParOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  StaticParOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.static_par", odsAttrs.getContext());
  }

  StaticParOpGenericAdaptorBase(StaticParOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class StaticParOpGenericAdaptor : public detail::StaticParOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::StaticParOpGenericAdaptorBase;
public:
  StaticParOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  StaticParOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : StaticParOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  StaticParOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : StaticParOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  StaticParOpGenericAdaptor(RangeT values, const StaticParOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = StaticParOp, typename = std::enable_if_t<std::is_same_v<LateInst, StaticParOp>>>
  StaticParOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class StaticParOpAdaptor : public StaticParOpGenericAdaptor<::mlir::ValueRange> {
public:
  using StaticParOpGenericAdaptor::StaticParOpGenericAdaptor;
  StaticParOpAdaptor(StaticParOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class StaticParOp : public ::mlir::Op<StaticParOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::OpInvariants, ::circt::calyx::ControlLike> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = StaticParOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = StaticParOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("calyx.static_par");
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static StaticParOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static StaticParOp create(::mlir::ImplicitLocOpBuilder &builder);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  /// Returns the body of a Calyx container.
  Block *getBodyBlock() {
    Region* region = &getOperation()->getRegion(0);
    assert(region->hasOneBlock() && "The body should have one Block.");
    return &region->front();
  }
};

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::StaticParOp)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::StaticRepeatOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class StaticRepeatOpGenericAdaptorBase {
public:
  struct Properties {
    using countTy = ::mlir::IntegerAttr;
    countTy count;

    auto getCount() const {
      auto &propStorage = this->count;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setCount(const ::mlir::IntegerAttr &propValue) {
      this->count = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.count == this->count &&
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
  StaticRepeatOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.static_repeat", odsAttrs.getContext());
  }

  StaticRepeatOpGenericAdaptorBase(StaticRepeatOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getCountAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().count);
    return attr;
  }

  uint32_t getCount();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class StaticRepeatOpGenericAdaptor : public detail::StaticRepeatOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::StaticRepeatOpGenericAdaptorBase;
public:
  StaticRepeatOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  StaticRepeatOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : StaticRepeatOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  StaticRepeatOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : StaticRepeatOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  StaticRepeatOpGenericAdaptor(RangeT values, const StaticRepeatOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = StaticRepeatOp, typename = std::enable_if_t<std::is_same_v<LateInst, StaticRepeatOp>>>
  StaticRepeatOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class StaticRepeatOpAdaptor : public StaticRepeatOpGenericAdaptor<::mlir::ValueRange> {
public:
  using StaticRepeatOpGenericAdaptor::StaticRepeatOpGenericAdaptor;
  StaticRepeatOpAdaptor(StaticRepeatOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class StaticRepeatOp : public ::mlir::Op<StaticRepeatOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::ControlLike> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = StaticRepeatOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = StaticRepeatOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("count")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getCountAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getCountAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("calyx.static_repeat");
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
  ::mlir::IntegerAttr getCountAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().count);
  }

  uint32_t getCount();
  void setCountAttr(::mlir::IntegerAttr attr) {
    getProperties().count = attr;
  }

  void setCount(uint32_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, uint32_t count);
  static StaticRepeatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, uint32_t count);
  static StaticRepeatOp create(::mlir::ImplicitLocOpBuilder &builder, uint32_t count);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
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
  /// Returns the body of a Calyx container.
  Block *getBodyBlock() {
    Region* region = &getOperation()->getRegion(0);
    assert(region->hasOneBlock() && "The body should have one Block.");
    return &region->front();
  }
};

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::StaticRepeatOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::StaticRepeatOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::StaticSeqOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class StaticSeqOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  StaticSeqOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.static_seq", odsAttrs.getContext());
  }

  StaticSeqOpGenericAdaptorBase(StaticSeqOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class StaticSeqOpGenericAdaptor : public detail::StaticSeqOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::StaticSeqOpGenericAdaptorBase;
public:
  StaticSeqOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  StaticSeqOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : StaticSeqOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  StaticSeqOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : StaticSeqOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  StaticSeqOpGenericAdaptor(RangeT values, const StaticSeqOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = StaticSeqOp, typename = std::enable_if_t<std::is_same_v<LateInst, StaticSeqOp>>>
  StaticSeqOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class StaticSeqOpAdaptor : public StaticSeqOpGenericAdaptor<::mlir::ValueRange> {
public:
  using StaticSeqOpGenericAdaptor::StaticSeqOpGenericAdaptor;
  StaticSeqOpAdaptor(StaticSeqOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class StaticSeqOp : public ::mlir::Op<StaticSeqOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::OpInvariants, ::circt::calyx::ControlLike> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = StaticSeqOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = StaticSeqOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("calyx.static_seq");
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static StaticSeqOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static StaticSeqOp create(::mlir::ImplicitLocOpBuilder &builder);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  /// Returns the body of a Calyx container.
  Block *getBodyBlock() {
    Region* region = &getOperation()->getRegion(0);
    assert(region->hasOneBlock() && "The body should have one Block.");
    return &region->front();
  }
};

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::StaticSeqOp)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::SubLibOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SubLibOpGenericAdaptorBase {
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
  SubLibOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.std_sub", odsAttrs.getContext());
  }

  SubLibOpGenericAdaptorBase(SubLibOp op);

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
class SubLibOpGenericAdaptor : public detail::SubLibOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SubLibOpGenericAdaptorBase;
public:
  SubLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SubLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SubLibOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SubLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SubLibOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SubLibOpGenericAdaptor(RangeT values, const SubLibOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SubLibOp, typename = std::enable_if_t<std::is_same_v<LateInst, SubLibOp>>>
  SubLibOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SubLibOpAdaptor : public SubLibOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SubLibOpGenericAdaptor::SubLibOpGenericAdaptor;
  SubLibOpAdaptor(SubLibOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SubLibOp : public ::mlir::Op<SubLibOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<3>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::Combinational, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SubLibOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SubLibOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<SubLibOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<SubLibOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<SubLibOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<SubLibOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<SubLibOp>::direction;
  using ::circt::calyx::CellInterface::Trait<SubLibOp>::portName;
  using ::circt::calyx::CellInterface::Trait<SubLibOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<SubLibOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<SubLibOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<SubLibOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<SubLibOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<SubLibOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<SubLibOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.std_sub");
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

  ::mlir::TypedValue<::mlir::Type> getLeft() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getRight() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(2).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static SubLibOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static SubLibOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::SubLibOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::SubLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::UndefLibOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class UndefLibOpGenericAdaptorBase {
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
  UndefLibOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.undefined", odsAttrs.getContext());
  }

  UndefLibOpGenericAdaptorBase(UndefLibOp op);

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
class UndefLibOpGenericAdaptor : public detail::UndefLibOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::UndefLibOpGenericAdaptorBase;
public:
  UndefLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  UndefLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : UndefLibOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  UndefLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : UndefLibOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  UndefLibOpGenericAdaptor(RangeT values, const UndefLibOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = UndefLibOp, typename = std::enable_if_t<std::is_same_v<LateInst, UndefLibOp>>>
  UndefLibOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class UndefLibOpAdaptor : public UndefLibOpGenericAdaptor<::mlir::ValueRange> {
public:
  using UndefLibOpGenericAdaptor::UndefLibOpGenericAdaptor;
  UndefLibOpAdaptor(UndefLibOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class UndefLibOp : public ::mlir::Op<UndefLibOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = UndefLibOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = UndefLibOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<UndefLibOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<UndefLibOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<UndefLibOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<UndefLibOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<UndefLibOp>::direction;
  using ::circt::calyx::CellInterface::Trait<UndefLibOp>::portName;
  using ::circt::calyx::CellInterface::Trait<UndefLibOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<UndefLibOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<UndefLibOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<UndefLibOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<UndefLibOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<UndefLibOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<UndefLibOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.undefined");
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

  ::mlir::TypedValue<::mlir::Type> getOut() {
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
  ::mlir::StringAttr getSymNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
  }

  ::llvm::StringRef getSymName();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static UndefLibOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static UndefLibOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::UndefLibOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::UndefLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::UndefinedOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class UndefinedOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  UndefinedOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.undef", odsAttrs.getContext());
  }

  UndefinedOpGenericAdaptorBase(UndefinedOp op);

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
class UndefinedOpGenericAdaptor : public detail::UndefinedOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::UndefinedOpGenericAdaptorBase;
public:
  UndefinedOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  UndefinedOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : UndefinedOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  UndefinedOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : UndefinedOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  UndefinedOpGenericAdaptor(RangeT values, const UndefinedOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = UndefinedOp, typename = std::enable_if_t<std::is_same_v<LateInst, UndefinedOp>>>
  UndefinedOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class UndefinedOpAdaptor : public UndefinedOpGenericAdaptor<::mlir::ValueRange> {
public:
  using UndefinedOpGenericAdaptor::UndefinedOpGenericAdaptor;
  UndefinedOpAdaptor(UndefinedOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class UndefinedOp : public ::mlir::Op<UndefinedOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = UndefinedOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = UndefinedOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("calyx.undef");
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

  ::mlir::TypedValue<::mlir::Type> getRes() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type res);
  static UndefinedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type res);
  static UndefinedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type res);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static UndefinedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static UndefinedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UndefinedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UndefinedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UndefinedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UndefinedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::UndefinedOp)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::WhileOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class WhileOpGenericAdaptorBase {
public:
  struct Properties {
    using groupNameTy = ::mlir::FlatSymbolRefAttr;
    groupNameTy groupName;

    auto getGroupName() const {
      auto &propStorage = this->groupName;
      return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setGroupName(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->groupName = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.groupName == this->groupName &&
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
  WhileOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.while", odsAttrs.getContext());
  }

  WhileOpGenericAdaptorBase(WhileOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getGroupNameAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().groupName);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getGroupName();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class WhileOpGenericAdaptor : public detail::WhileOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::WhileOpGenericAdaptorBase;
  static constexpr int odsIndex_cond = 0;
public:
  WhileOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  WhileOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : WhileOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  WhileOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : WhileOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  WhileOpGenericAdaptor(RangeT values, const WhileOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = WhileOp, typename = std::enable_if_t<std::is_same_v<LateInst, WhileOp>>>
  WhileOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getCond() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class WhileOpAdaptor : public WhileOpGenericAdaptor<::mlir::ValueRange> {
public:
  using WhileOpGenericAdaptor::WhileOpGenericAdaptor;
  WhileOpAdaptor(WhileOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class WhileOp : public ::mlir::Op<WhileOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::ControlLike> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = WhileOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = WhileOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_cond = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("groupName")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getGroupNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getGroupNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("calyx.while");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getCond() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getCondMutable() {
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
  ::mlir::FlatSymbolRefAttr getGroupNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::FlatSymbolRefAttr>(getProperties().groupName);
  }

  ::std::optional< ::llvm::StringRef > getGroupName();
  void setGroupNameAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().groupName = attr;
  }

  void setGroupName(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeGroupNameAttr() {
      auto attr = getProperties().groupName;
      getProperties().groupName = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value cond, FlatSymbolRefAttr groupName = nullptr);
  static WhileOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value cond, FlatSymbolRefAttr groupName = nullptr);
  static WhileOp create(::mlir::ImplicitLocOpBuilder &builder, Value cond, FlatSymbolRefAttr groupName = nullptr);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult canonicalize(WhileOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
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
  /// Returns the body of a Calyx container.
  Block *getBodyBlock() {
    Region* region = &getOperation()->getRegion(0);
    assert(region->hasOneBlock() && "The body should have one Block.");
    return &region->front();
  }
};

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::WhileOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::WhileOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::WireLibOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class WireLibOpGenericAdaptorBase {
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
  WireLibOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.std_wire", odsAttrs.getContext());
  }

  WireLibOpGenericAdaptorBase(WireLibOp op);

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
class WireLibOpGenericAdaptor : public detail::WireLibOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::WireLibOpGenericAdaptorBase;
public:
  WireLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  WireLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : WireLibOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  WireLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : WireLibOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  WireLibOpGenericAdaptor(RangeT values, const WireLibOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = WireLibOp, typename = std::enable_if_t<std::is_same_v<LateInst, WireLibOp>>>
  WireLibOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class WireLibOpAdaptor : public WireLibOpGenericAdaptor<::mlir::ValueRange> {
public:
  using WireLibOpGenericAdaptor::WireLibOpGenericAdaptor;
  WireLibOpAdaptor(WireLibOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class WireLibOp : public ::mlir::Op<WireLibOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<2>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::Combinational, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = WireLibOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = WireLibOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<WireLibOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<WireLibOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<WireLibOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<WireLibOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<WireLibOp>::direction;
  using ::circt::calyx::CellInterface::Trait<WireLibOp>::portName;
  using ::circt::calyx::CellInterface::Trait<WireLibOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<WireLibOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<WireLibOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<WireLibOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<WireLibOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<WireLibOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<WireLibOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.std_wire");
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

  ::mlir::TypedValue<::mlir::IntegerType> getIn() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(1).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::Type wireType);
  static WireLibOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::Type wireType);
  static WireLibOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::Type wireType);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::WireLibOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::WireLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::WiresOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class WiresOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  WiresOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.wires", odsAttrs.getContext());
  }

  WiresOpGenericAdaptorBase(WiresOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class WiresOpGenericAdaptor : public detail::WiresOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::WiresOpGenericAdaptorBase;
public:
  WiresOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  WiresOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : WiresOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  WiresOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : WiresOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  WiresOpGenericAdaptor(RangeT values, const WiresOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = WiresOp, typename = std::enable_if_t<std::is_same_v<LateInst, WiresOp>>>
  WiresOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class WiresOpAdaptor : public WiresOpGenericAdaptor<::mlir::ValueRange> {
public:
  using WiresOpGenericAdaptor::WiresOpGenericAdaptor;
  WiresOpAdaptor(WiresOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class WiresOp : public ::mlir::Op<WiresOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<ComponentOp, CombComponentOp>::Impl, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::SymbolTable, ::mlir::RegionKindInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = WiresOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = WiresOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("calyx.wires");
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static WiresOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static WiresOp create(::mlir::ImplicitLocOpBuilder &builder);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  /// Implement RegionKindInterface.
  static RegionKind getRegionKind(unsigned index) { return RegionKind::Graph; }

  /// Returns the body of a Calyx component.
  Block *getBodyBlock() {
    Region* region = &getOperation()->getRegion(0);
    assert(region->hasOneBlock() && "The body should have one Block.");
    return &region->front();
  }

};

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::WiresOp)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::XorLibOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class XorLibOpGenericAdaptorBase {
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
  XorLibOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("calyx.std_xor", odsAttrs.getContext());
  }

  XorLibOpGenericAdaptorBase(XorLibOp op);

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
class XorLibOpGenericAdaptor : public detail::XorLibOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::XorLibOpGenericAdaptorBase;
public:
  XorLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  XorLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : XorLibOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  XorLibOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : XorLibOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  XorLibOpGenericAdaptor(RangeT values, const XorLibOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = XorLibOp, typename = std::enable_if_t<std::is_same_v<LateInst, XorLibOp>>>
  XorLibOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class XorLibOpAdaptor : public XorLibOpGenericAdaptor<::mlir::ValueRange> {
public:
  using XorLibOpGenericAdaptor::XorLibOpGenericAdaptor;
  XorLibOpAdaptor(XorLibOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class XorLibOp : public ::mlir::Op<XorLibOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::NResults<3>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::calyx::Combinational, ::circt::calyx::CellInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = XorLibOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = XorLibOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::calyx::CellInterface::Trait<XorLibOp>::instanceName;
  using ::circt::calyx::CellInterface::Trait<XorLibOp>::portIndex;
  using ::circt::calyx::CellInterface::Trait<XorLibOp>::getPortInfo;
  using ::circt::calyx::CellInterface::Trait<XorLibOp>::portInfo;
  using ::circt::calyx::CellInterface::Trait<XorLibOp>::direction;
  using ::circt::calyx::CellInterface::Trait<XorLibOp>::portName;
  using ::circt::calyx::CellInterface::Trait<XorLibOp>::portDictionaryAttr;
  using ::circt::calyx::CellInterface::Trait<XorLibOp>::getInputPorts;
  using ::circt::calyx::CellInterface::Trait<XorLibOp>::getOutputPorts;
  using ::circt::calyx::CellInterface::Trait<XorLibOp>::filterInterfacePorts;
  using ::mlir::OpAsmOpInterface::Trait<XorLibOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<XorLibOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<XorLibOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("calyx.std_xor");
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

  ::mlir::TypedValue<::mlir::Type> getLeft() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getRight() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getOut() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(2).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static XorLibOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes);
  static XorLibOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  SmallVector<StringRef> portNames();
  SmallVector<circt::calyx::Direction> portDirections();
  SmallVector<DictionaryAttr> portAttributes();
  bool isCombinational();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::calyx
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::XorLibOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::calyx::detail::XorLibOpGenericAdaptorBase::Properties)


#endif // GET_OP_CLASSES

