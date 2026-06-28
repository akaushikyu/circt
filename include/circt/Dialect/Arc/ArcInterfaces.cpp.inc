/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Allows non-clocked counterparts to clocked operations (e.g., `arc.call`)
/// to implement this interface to simplify the implementation of some
/// passes.
bool circt::arc::ClockedOpInterface::isClocked() {
      return getImpl()->isClocked();
  }

/// Returns the SSA value representing the clock signal. It is valid to
/// return a null value if the operation is inside a clocked region and thus
/// the clock is defined by the operation with the clocked region, or if the
/// operation is not clocked as determined by the `isClocked` static
/// function.
::mlir::Value circt::arc::ClockedOpInterface::getClock() {
      return getImpl()->getClock(getImpl(), getOperation());
  }

/// Removes the clock value, e.g., used when moving a clocked operation into
/// a clocked region. If the operation already does not have a clock, this
/// should be a nop.
void circt::arc::ClockedOpInterface::eraseClock() {
      return getImpl()->eraseClock(getImpl(), getOperation());
  }

/// Returns the latency w.r.t. to the clock returned by the `getClock`
/// function.
uint32_t circt::arc::ClockedOpInterface::getLatency() {
      return getImpl()->getLatency(getImpl(), getOperation());
  }
