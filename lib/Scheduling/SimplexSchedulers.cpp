//===- SimplexSchedulers.cpp - Linear programming-based schedulers --------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Implementation of linear programming-based schedulers with a built-in simplex
// solver.
//
//===----------------------------------------------------------------------===//

#include "circt/Scheduling/Algorithms.h"
#include "circt/Scheduling/Utilities.h"

#include "mlir/IR/Operation.h"

#include "llvm/ADT/DenseMap.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/Format.h"

#include <algorithm>
#include <limits>

#define DEBUG_TYPE "simplex-schedulers"

using namespace circt;
using namespace circt::scheduling;

using llvm::dbgs;
using llvm::format;

namespace {

/// MODIFIED (hls-est W9 round 23 review D9): the simplex tableau in one
/// row-major buffer. The schedulers scan single columns across every row
/// (the pivot column of a pivot, the ratio tests); with one heap block per
/// row each such access missed the cache twice (row header and row data).
/// Rows are built once (buildTableau) and never added afterwards. The
/// arithmetic is unchanged, so are the schedules.
class FlatTableau {
public:
  MutableArrayRef<int> operator[](unsigned row) {
    return MutableArrayRef<int>(rowData(row), stride);
  }
  ArrayRef<int> operator[](unsigned row) const {
    return ArrayRef<int>(rowData(row), stride);
  }
  int *rowData(unsigned row) { return data.data() + size_t(row) * stride; }
  const int *rowData(unsigned row) const {
    return data.data() + size_t(row) * stride;
  }
  unsigned size() const { return rows; }
  /// The rows of `built`, each `columns` wide.
  void assign(ArrayRef<SmallVector<int>> built, unsigned columns) {
    stride = columns;
    rows = built.size();
    data.assign(size_t(rows) * stride, 0);
    for (unsigned r = 0; r < rows; ++r)
      std::copy(built[r].begin(), built[r].end(), rowData(r));
  }

private:
  std::vector<int> data;
  unsigned stride = 0, rows = 0;
};

/// This class provides a framework to model certain scheduling problems as
/// lexico-parametric linear programs (LP), which are then solved with an
/// extended version of the dual simplex algorithm.
///
/// The approach is described in:
///  [1] B. D. de Dinechin, "Simplex Scheduling: More than Lifetime-Sensitive
///      Instruction Scheduling", PRISM 1994.22, 1994.
///  [2] B. D. de Dinechin, "Fast Modulo Scheduling Under the Simplex Scheduling
///      Framework", PRISM 1995.01, 1995.
///
/// Resource-free scheduling problems (called "central problems" in the papers)
/// have an *integer* linear programming formulation with a totally unimodular
/// constraint matrix. Such ILPs can however be solved optimally in polynomial
/// time with a (non-integer) LP solver (such as the simplex algorithm), as the
/// LP solution is guaranteed to be integer. Note that this is the same idea as
/// used by SDC-based schedulers.
class SimplexSchedulerBase {
protected:
  /// The objective is to minimize the start time of this operation.
  Operation *lastOp;

  /// MODIFIED (hls-est T7, OPEN_ISSUES O9): set when scheduleAt() could not
  /// restore a feasible tableau after rolling back a failed fixation (an
  /// assertion before). Every later result of the tableau is meaningless, so
  /// the modulo scheduler reports a failure and its caller falls back to
  /// another scheduler.
  bool tableauInvalid = false;

  /// S is part of a mechanism to assign fixed values to the LP variables.
  int parameterS;

  /// T represents the initiation interval (II). Its minimally-feasible value is
  /// computed by the algorithm.
  int parameterT;

  /// The simplex tableau is the algorithm's main data structure.
  /// The dashed parts always contain the zero respectively the identity matrix,
  /// and therefore are not stored explicitly.
  ///
  ///                        ◀───nColumns────▶
  ///           nParameters────┐
  ///                        ◀─┴─▶
  ///                       ┌─────┬───────────┬ ─ ─ ─ ─ ┐
  ///                      ▲│. . .│. . ... . .│    0        ▲
  ///           nObjectives││. . .│. . ... . .│         │   │
  ///                      ▼│. . .│. . ... . .│             │
  ///                       ├─────┼───────────┼ ─ ─ ─ ─ ┤   │
  ///  firstConstraintRow > │. . .│. . ... . .│1            │nRows
  ///                       │. . .│. . ... . .│  1      │   │
  ///                       │. . .│. . ... . .│    1        │
  ///                       │. . .│. . ... . .│      1  │   │
  ///                       │. . .│. . ... . .│        1    ▼
  ///                       └─────┴───────────┴ ─ ─ ─ ─ ┘
  ///       parameter1Column ^
  ///         parameterSColumn ^
  ///           parameterTColumn ^
  ///  firstNonBasicVariableColumn ^
  ///                              ─────────── ──────────
  ///                       nonBasicVariables   basicVariables
  FlatTableau tableau;

  /// During the pivot operation, one column in the elided part of the tableau
  /// is modified; this vector temporarily catches the changes.
  SmallVector<int> implicitBasicVariableColumnVector;

  /// The linear program models the operations' start times as variables, which
  /// we identify here as 0, ..., |ops|-1.
  /// Additionally, for each dependence (precisely, the inequality modeling the
  /// precedence constraint), a slack variable is required; these are identified
  /// as |ops|, ..., |ops|+|deps|-1.
  ///
  /// This vector stores the numeric IDs of non-basic variables. A variable's
  /// index *i* in this vector corresponds to the tableau *column*
  /// `firstNonBasicVariableColumn`+*i*.
  SmallVector<unsigned> nonBasicVariables;

  /// This vector store the numeric IDs of basic variables. A variable's index
  /// *i* in this vector corresponds to the tableau *row*
  /// `firstConstraintRow`+*i*.
  SmallVector<unsigned> basicVariables;

  /// Used to conveniently retrieve an operation's start time variable. The
  /// alternative would be to find the op's index in the problem's list of
  /// operations.
  DenseMap<Operation *, unsigned> startTimeVariables;

  /// This vector keeps track of the current locations (i.e. row or column) of
  /// a start time variable in the tableau. We encode column numbers as positive
  /// integers, and row numbers as negative integers. We do not track the slack
  /// variables.
  SmallVector<int> startTimeLocations;

  /// Non-basic variables can be "frozen" to a specific value, which prevents
  /// them from being pivoted into basis again.
  DenseMap<unsigned, unsigned> frozenVariables;
  /// MODIFIED (hls-est T7): `frozenVariables.count(var)` as a flag per variable
  /// (start time and slack variables), so that the pivot searches do not hash
  /// once per column. Kept in sync with `frozenVariables` by freeze() and
  /// scheduleAt().
  SmallVector<char> frozenFlags;
  bool isFrozen(unsigned var) const {
    return var < frozenFlags.size() && frozenFlags[var];
  }

  /// Number of rows in the tableau = |obj| + |deps|.
  unsigned nRows;
  /// Number of explicitly stored columns in the tableau = |params| + |ops|.
  unsigned nColumns;

  // Number of objective rows.
  unsigned nObjectives;
  /// All other rows encode linear constraints.
  unsigned &firstConstraintRow = nObjectives;

  // Number of parameters (fixed for now).
  static constexpr unsigned nParameters = 3;
  /// The first column corresponds to the always-one "parameter" in u = (1,S,T).
  static constexpr unsigned parameter1Column = 0;
  /// The second column corresponds to the variable-freezing parameter S.
  static constexpr unsigned parameterSColumn = 1;
  /// The third column corresponds to the parameter T, i.e. the current II.
  static constexpr unsigned parameterTColumn = 2;
  /// All other (explicitly stored) columns represent non-basic variables.
  static constexpr unsigned firstNonBasicVariableColumn = nParameters;

  /// Allow subclasses to collect additional constraints that are not part of
  /// the input problem, but should be modeled in the linear problem.
  SmallVector<Problem::Dependence> additionalConstraints;

  virtual Problem &getProblem() = 0;
  virtual LogicalResult checkLastOp();
  virtual bool fillObjectiveRow(SmallVector<int> &row, unsigned obj);
  virtual void fillConstraintRow(SmallVector<int> &row,
                                 Problem::Dependence dep);
  virtual void fillAdditionalConstraintRow(SmallVector<int> &row,
                                           Problem::Dependence dep);
  void buildTableau();

  int getParametricConstant(unsigned row);
  SmallVector<int> getObjectiveVector(unsigned column);
  std::optional<unsigned> findDualPivotRow();
  std::optional<unsigned> findDualPivotColumn(unsigned pivotRow,
                                              bool allowPositive = false);
  std::optional<unsigned> findPrimalPivotColumn();
  std::optional<unsigned> findPrimalPivotRow(unsigned pivotColumn);
  void multiplyRow(unsigned row, int factor);
  void addMultipleOfRow(unsigned sourceRow, int factor, unsigned targetRow);
  void pivot(unsigned pivotRow, unsigned pivotColumn);
  LogicalResult solveTableau();
  LogicalResult restoreDualFeasibility();
  bool isInBasis(unsigned startTimeVariable);
  std::optional<unsigned> freeze(unsigned startTimeVariable,
                                 unsigned timeStep);
  void translate(unsigned column, int factor1, int factorS, int factorT);
  LogicalResult scheduleAt(unsigned startTimeVariable, unsigned timeStep);
  void moveBy(unsigned startTimeVariable, unsigned amount);
  unsigned getStartTime(unsigned startTimeVariable);

  void dumpTableau();

  /// MODIFIED (hls-est W9 round 23 review D9): per variable column (not the
  /// parameter columns), the rows whose entry may be non-zero, so that the
  /// column scans (the pivot column of a pivot, the primal ratio test, a
  /// translation) visit those rows instead of every row: a superset (a row
  /// whose entry became 0 stays until a scan drops it), each row at most
  /// once (`columnMember`). The visiting order differs from the row order;
  /// the scans do not depend on it (the ratio test breaks ties on the
  /// smallest row, as the ascending scan did).
  SmallVector<SmallVector<unsigned>> columnRows;
  std::vector<uint8_t> columnMember; // nRows x nColumns
  void buildColumnIndex();
  void noteNonZero(unsigned row, unsigned col) {
    if (col < firstNonBasicVariableColumn)
      return;
    uint8_t &m = columnMember[size_t(row) * nColumns + col];
    if (!m) {
      m = 1;
      columnRows[col].push_back(row);
    }
  }
  /// The rows of `col` whose entry is non-zero (stale rows are dropped).
  template <typename Fn> void forEachNonZeroRow(unsigned col, Fn fn) {
    if (col < firstNonBasicVariableColumn) {
      for (unsigned row = 0; row < nRows; ++row)
        if (tableau.rowData(row)[col] != 0)
          fn(row);
      return;
    }
    SmallVector<unsigned> &rows = columnRows[col];
    unsigned keep = 0;
    for (unsigned i = 0, e = rows.size(); i < e; ++i) {
      unsigned row = rows[i];
      if (tableau.rowData(row)[col] == 0) {
        columnMember[size_t(row) * nColumns + col] = 0;
        continue;
      }
      rows[keep++] = row;
    }
    rows.truncate(keep);
    for (unsigned row : rows)
      fn(row);
  }

public:
  explicit SimplexSchedulerBase(Operation *lastOp) : lastOp(lastOp) {}
  virtual ~SimplexSchedulerBase() = default;
  virtual LogicalResult schedule() = 0;
};

/// This class solves the basic, acyclic `Problem`.
class SimplexScheduler : public SimplexSchedulerBase {
private:
  Problem &prob;

protected:
  Problem &getProblem() override { return prob; }

public:
  SimplexScheduler(Problem &prob, Operation *lastOp)
      : SimplexSchedulerBase(lastOp), prob(prob) {}

  LogicalResult schedule() override;
};

/// This class solves the resource-free `CyclicProblem`.  The optimal initiation
/// interval (II) is determined as a side product of solving the parametric
/// problem, and corresponds to the "RecMII" (= recurrence-constrained minimum
/// II) usually considered as one component in the lower II bound used by modulo
/// schedulers.
class CyclicSimplexScheduler : public SimplexSchedulerBase {
private:
  CyclicProblem &prob;

protected:
  Problem &getProblem() override { return prob; }
  void fillConstraintRow(SmallVector<int> &row,
                         Problem::Dependence dep) override;

public:
  CyclicSimplexScheduler(CyclicProblem &prob, Operation *lastOp)
      : SimplexSchedulerBase(lastOp), prob(prob) {}
  LogicalResult schedule() override;
};

// This class solves acyclic, resource-constrained `SharedOperatorsProblem` with
// a simplified version of the iterative heuristic presented in [2].
class SharedOperatorsSimplexScheduler : public SimplexSchedulerBase {
private:
  SharedOperatorsProblem &prob;

protected:
  Problem &getProblem() override { return prob; }

public:
  SharedOperatorsSimplexScheduler(SharedOperatorsProblem &prob,
                                  Operation *lastOp)
      : SimplexSchedulerBase(lastOp), prob(prob) {}
  LogicalResult schedule() override;
};

// This class solves the `ModuloProblem` using the iterative heuristic presented
// in [2].
class ModuloSimplexScheduler : public CyclicSimplexScheduler {
private:
  struct MRT {
    ModuloSimplexScheduler &sched;

    using TableType = SmallDenseMap<unsigned, DenseSet<Operation *>>;
    using ReverseTableType = SmallDenseMap<Operation *, unsigned>;
    SmallDenseMap<Problem::ResourceType, TableType> tables;
    SmallDenseMap<Problem::ResourceType, ReverseTableType> reverseTables;

    explicit MRT(ModuloSimplexScheduler &sched) : sched(sched) {}
    LogicalResult enter(Operation *op, unsigned timeStep);
    void release(Operation *op);
  };

  ModuloProblem &prob;
  SmallVector<unsigned> asapTimes, alapTimes;
  SmallVector<Operation *> unscheduled, scheduled;
  MRT mrt;

protected:
  Problem &getProblem() override { return prob; }
  LogicalResult checkLastOp() override;
  enum { OBJ_LATENCY = 0, OBJ_AXAP /* i.e. either ASAP or ALAP */ };
  bool fillObjectiveRow(SmallVector<int> &row, unsigned obj) override;
  LogicalResult updateMargins();
  LogicalResult scheduleOperation(Operation *n);
  unsigned computeResMinII();

public:
  ModuloSimplexScheduler(ModuloProblem &prob, Operation *lastOp)
      : CyclicSimplexScheduler(prob, lastOp), prob(prob), mrt(*this) {}
  LogicalResult schedule() override;
};

// This class solves the `ChainingProblem` by relying on pre-computed
// chain-breaking constraints.
class ChainingSimplexScheduler : public SimplexSchedulerBase {
private:
  ChainingProblem &prob;
  float cycleTime;

protected:
  Problem &getProblem() override { return prob; }
  void fillAdditionalConstraintRow(SmallVector<int> &row,
                                   Problem::Dependence dep) override;

public:
  ChainingSimplexScheduler(ChainingProblem &prob, Operation *lastOp,
                           float cycleTime)
      : SimplexSchedulerBase(lastOp), prob(prob), cycleTime(cycleTime) {}
  LogicalResult schedule() override;
};

// This class solves the resource-free `ChainingCyclicProblem` by relying on
// pre-computed chain-breaking constraints. The optimal initiation interval (II)
// is determined as a side product of solving the parametric problem, and
// corresponds to the "RecMII" (= recurrence-constrained minimum II) usually
// considered as one component in the lower II bound used by modulo schedulers.
class ChainingCyclicSimplexScheduler : public SimplexSchedulerBase {
private:
  ChainingCyclicProblem &prob;
  float cycleTime;

protected:
  Problem &getProblem() override { return prob; }
  void fillConstraintRow(SmallVector<int> &row,
                         Problem::Dependence dep) override;
  void fillAdditionalConstraintRow(SmallVector<int> &row,
                                   Problem::Dependence dep) override;

public:
  ChainingCyclicSimplexScheduler(ChainingCyclicProblem &prob, Operation *lastOp,
                                 float cycleTime)
      : SimplexSchedulerBase(lastOp), prob(prob), cycleTime(cycleTime) {}
  LogicalResult schedule() override;
};

} // anonymous namespace

//===----------------------------------------------------------------------===//
// SimplexSchedulerBase
//===----------------------------------------------------------------------===//

LogicalResult SimplexSchedulerBase::checkLastOp() {
  auto &prob = getProblem();
  if (!prob.hasOperation(lastOp))
    return prob.getContainingOp()->emitError(
        "problem does not include last operation");
  return success();
}

bool SimplexSchedulerBase::fillObjectiveRow(SmallVector<int> &row,
                                            unsigned obj) {
  assert(obj == 0);
  // Minimize start time of user-specified last operation.
  row[startTimeLocations[startTimeVariables[lastOp]]] = 1;
  return false;
}

void SimplexSchedulerBase::fillConstraintRow(SmallVector<int> &row,
                                             Problem::Dependence dep) {
  auto &prob = getProblem();
  Operation *src = dep.getSource();
  Operation *dst = dep.getDestination();
  unsigned latency = *prob.getLatency(*prob.getLinkedOperatorType(src));
  row[parameter1Column] = -latency; // note the negation
  if (src != dst) { // note that these coefficients just zero out in self-arcs.
    row[startTimeLocations[startTimeVariables[src]]] = 1;
    row[startTimeLocations[startTimeVariables[dst]]] = -1;
  }
}

void SimplexSchedulerBase::fillAdditionalConstraintRow(
    SmallVector<int> &row, Problem::Dependence dep) {
  // Handling is subclass-specific, so do nothing by default.
  (void)row;
  (void)dep;
}

void SimplexSchedulerBase::buildTableau() {
  auto &prob = getProblem();

  // The initial tableau is constructed so that operations' start time variables
  // are out of basis, whereas all slack variables are in basis. We will number
  // them accordingly.
  unsigned var = 0;

  // Assign column and variable numbers to the operations' start times.
  for (auto *op : prob.getOperations()) {
    nonBasicVariables.push_back(var);
    startTimeVariables[op] = var;
    startTimeLocations.push_back(firstNonBasicVariableColumn + var);
    ++var;
  }

  // one column for each parameter (1,S,T), and for all operations
  nColumns = nParameters + nonBasicVariables.size();

  // Helper to grow both the tableau and the implicit column vector.
  SmallVector<SmallVector<int>> rows;
  auto addRow = [&]() -> SmallVector<int> & {
    implicitBasicVariableColumnVector.push_back(0);
    return rows.emplace_back(nColumns, 0);
  };

  // Set up the objective rows.
  nObjectives = 0;
  bool hasMoreObjectives;
  do {
    auto &objRowVec = addRow();
    hasMoreObjectives = fillObjectiveRow(objRowVec, nObjectives);
    ++nObjectives;
  } while (hasMoreObjectives);

  // Now set up rows/constraints for the dependences.
  for (auto *op : prob.getOperations()) {
    for (auto &dep : prob.getDependences(op)) {
      auto &consRowVec = addRow();
      fillConstraintRow(consRowVec, dep);
      basicVariables.push_back(var);
      ++var;
    }
  }
  for (auto &dep : additionalConstraints) {
    auto &consRowVec = addRow();
    fillAdditionalConstraintRow(consRowVec, dep);
    basicVariables.push_back(var);
    ++var;
  }

  // one row per objective + one row per dependence
  tableau.assign(rows, nColumns);
  nRows = tableau.size();
  buildColumnIndex();
  frozenFlags.assign(var, 0);
}

void SimplexSchedulerBase::buildColumnIndex() {
  columnRows.assign(nColumns, {});
  columnMember.assign(size_t(nRows) * nColumns, 0);
  for (unsigned row = 0; row < nRows; ++row) {
    const int *rowVec = tableau.rowData(row);
    for (unsigned col = firstNonBasicVariableColumn; col < nColumns; ++col)
      if (rowVec[col] != 0)
        noteNonZero(row, col);
  }
}

int SimplexSchedulerBase::getParametricConstant(unsigned row) {
  const int *rowVec = tableau[row].data();
  // Compute the dot-product ~B[row] * u between the constant matrix and the
  // parameter vector.
  return rowVec[parameter1Column] + rowVec[parameterSColumn] * parameterS +
         rowVec[parameterTColumn] * parameterT;
}

SmallVector<int> SimplexSchedulerBase::getObjectiveVector(unsigned column) {
  SmallVector<int> objVec;
  // Extract the column vector C^T[column] from the cost matrix.
  for (unsigned obj = 0; obj < nObjectives; ++obj)
    objVec.push_back(tableau[obj][column]);
  return objVec;
}

std::optional<unsigned> SimplexSchedulerBase::findDualPivotRow() {
  // Find the first row in which the parametric constant is negative.
  for (unsigned row = firstConstraintRow; row < nRows; ++row)
    if (getParametricConstant(row) < 0)
      return row;

  return std::nullopt;
}

std::optional<unsigned>
SimplexSchedulerBase::findDualPivotColumn(unsigned pivotRow,
                                          bool allowPositive) {
  SmallVector<int> maxQuot(nObjectives, std::numeric_limits<int>::min());
  std::optional<unsigned> pivotCol;
  // MODIFIED (hls-est T7): raw rows and an in-place lexicographic comparison
  // instead of a quotient vector per candidate (same choice: a candidate wins
  // iff its quotient vector is lexicographically greater than the best one).
  SmallVector<const int *, 4> objRows;
  for (unsigned obj = 0; obj < nObjectives; ++obj)
    objRows.push_back(tableau[obj].data());
  const int *pivotRowVec = tableau[pivotRow].data();

  // Look for non-zero entries in the constraint matrix (~A part of the
  // tableau). If multiple candidates exist, take the one corresponding to the
  // lexicographical maximum (over the objective rows) of the quotients:
  //   tableau[<objective row>][col] / pivotCand
  for (unsigned col = firstNonBasicVariableColumn; col < nColumns; ++col) {
    if (isFrozen(nonBasicVariables[col - firstNonBasicVariableColumn]))
      continue;

    int pivotCand = pivotRowVec[col];
    // Only negative candidates bring us closer to the optimal solution.
    // However, when freezing variables to a certain value, we accept that the
    // value of the objective function degrades.
    if (pivotCand < 0 || (allowPositive && pivotCand > 0)) {
      // The constraint matrix has only {-1, 0, 1} entries by construction.
      assert(pivotCand * pivotCand == 1);

      bool greater = false;
      for (unsigned obj = 0; obj < nObjectives; ++obj) {
        int quot = objRows[obj][col] / pivotCand;
        if (quot != maxQuot[obj]) {
          greater = maxQuot[obj] < quot;
          break;
        }
      }
      if (greater) {
        for (unsigned obj = 0; obj < nObjectives; ++obj)
          maxQuot[obj] = objRows[obj][col] / pivotCand;
        pivotCol = col;
      }
    }
  }

  return pivotCol;
}

std::optional<unsigned> SimplexSchedulerBase::findPrimalPivotColumn() {
  // Find the first lexico-negative column in the cost matrix. MODIFIED
  // (hls-est T7): compared in place (a column is lexico-negative iff its first
  // non-zero cost is negative) instead of through a copied vector.
  SmallVector<const int *, 4> objRows;
  for (unsigned obj = 0; obj < nObjectives; ++obj)
    objRows.push_back(tableau[obj].data());
  for (unsigned col = firstNonBasicVariableColumn; col < nColumns; ++col) {
    if (isFrozen(nonBasicVariables[col - firstNonBasicVariableColumn]))
      continue;

    for (unsigned obj = 0; obj < nObjectives; ++obj) {
      int cost = objRows[obj][col];
      if (cost < 0)
        return col;
      if (cost > 0)
        break;
    }
  }

  return std::nullopt;
}

std::optional<unsigned>
SimplexSchedulerBase::findPrimalPivotRow(unsigned pivotColumn) {
  int minQuot = std::numeric_limits<int>::max();
  std::optional<unsigned> pivotRow;

  // Look for positive entries in the constraint matrix (~A part of the
  // tableau). If multiple candidates exist, take the one corresponding to the
  // minimum of the quotient:
  //   parametricConstant(row) / pivotCand
  forEachNonZeroRow(pivotColumn, [&](unsigned row) {
    if (row < firstConstraintRow)
      return;
    int pivotCand = tableau.rowData(row)[pivotColumn];
    if (pivotCand > 0) {
      // The constraint matrix has only {-1, 0, 1} entries by construction.
      assert(pivotCand == 1);
      int quot = getParametricConstant(row) / pivotCand;
      if (quot < minQuot || (pivotRow && quot == minQuot && row < *pivotRow)) {
        minQuot = quot;
        pivotRow = row;
      }
    }
  });

  return pivotRow;
}

void SimplexSchedulerBase::multiplyRow(unsigned row, int factor) {
  assert(factor != 0);
  int *rowVec = tableau[row].data();
  for (unsigned col = 0; col < nColumns; ++col)
    rowVec[col] *= factor;
  // Also multiply the corresponding entry in the temporary column vector.
  implicitBasicVariableColumnVector[row] *= factor;
}

void SimplexSchedulerBase::addMultipleOfRow(unsigned sourceRow, int factor,
                                            unsigned targetRow) {
  assert(factor != 0 && sourceRow != targetRow);
  const int *src = tableau[sourceRow].data();
  int *dst = tableau[targetRow].data();
  for (unsigned col = 0; col < nColumns; ++col)
    dst[col] += src[col] * factor;
  // Again, perform row operation on the temporary column vector as well.
  implicitBasicVariableColumnVector[targetRow] +=
      implicitBasicVariableColumnVector[sourceRow] * factor;
}

/// The pivot operation applies elementary row operations to the tableau in
/// order to make the \p pivotColumn (corresponding to a non-basic variable) a
/// unit vector (only the \p pivotRow'th entry is 1). Then, a basis exchange is
/// performed: the non-basic variable is swapped with the basic variable
/// associated with the pivot row.
void SimplexSchedulerBase::pivot(unsigned pivotRow, unsigned pivotColumn) {
  // The implicit columns are part of an identity matrix.
  implicitBasicVariableColumnVector[pivotRow] = 1;

  int pivotElem = tableau[pivotRow][pivotColumn];
  // The constraint matrix has only {-1, 0, 1} entries by construction.
  assert(pivotElem * pivotElem == 1);
  // Make `tableau[pivotRow][pivotColumn]` := 1
  multiplyRow(pivotRow, 1 / pivotElem);

  // MODIFIED (hls-est T7): addMultipleOfRow restricted to the non-zero columns
  // of the pivot row (every other column would gain 0), on raw rows: the same
  // arithmetic on every entry that changes. The dense row loop was the hot
  // spot of --convert-affine-to-loopschedule on user-unrolled bodies.
  const int *pivotRowVec = tableau[pivotRow].data();
  SmallVector<unsigned> nonZeroCols;
  for (unsigned col = 0; col < nColumns; ++col)
    if (pivotRowVec[col] != 0)
      nonZeroCols.push_back(col);
  const unsigned *nzBegin = nonZeroCols.data();
  const unsigned *nzEnd = nzBegin + nonZeroCols.size();
  int pivotImplicit = implicitBasicVariableColumnVector[pivotRow];

  // MODIFIED (hls-est W9 round 23 review D9): one pass over the rows, which
  // also swaps the pivot column with the implicitly constructed column vector
  // (the former pivot column is a unit vector, not stored explicitly). Every
  // implicit entry is 0 at the start of a pivot but the pivot row's, and a
  // row whose pivot-column entry is 0 is left as it is (its entry stays 0,
  // its implicit entry too), so only the rows that change are written.
  // The rows the pivot changes: those with a non-zero pivot-column entry.
  SmallVector<unsigned> changed;
  forEachNonZeroRow(pivotColumn, [&](unsigned row) {
    if (row != pivotRow)
      changed.push_back(row);
  });
  for (unsigned row : changed) {
    int *rowVec = tableau.rowData(row);
    int elem = rowVec[pivotColumn];

    // Make `tableau[row][pivotColumn]` := 0.
    int factor = -elem;
    for (const unsigned *col = nzBegin; col != nzEnd; ++col) {
      int &entry = rowVec[*col];
      bool wasZero = entry == 0;
      entry += pivotRowVec[*col] * factor;
      if (wasZero && entry != 0 && *col != pivotColumn)
        noteNonZero(row, *col);
    }
    implicitBasicVariableColumnVector[row] += pivotImplicit * factor;
    rowVec[pivotColumn] = implicitBasicVariableColumnVector[row];
    implicitBasicVariableColumnVector[row] = 0; // Reset for next pivot step.
  }
  tableau.rowData(pivotRow)[pivotColumn] =
      implicitBasicVariableColumnVector[pivotRow];
  implicitBasicVariableColumnVector[pivotRow] = 0;
  // The pivot column is now the former implicit column: non-zero exactly in
  // the changed rows and the pivot row (their implicit entries are +-1 times
  // a non-zero factor), which are already its rows.

  // Look up numeric IDs of variables involved in this pivot operation.
  unsigned &nonBasicVar =
      nonBasicVariables[pivotColumn - firstNonBasicVariableColumn];
  unsigned &basicVar = basicVariables[pivotRow - firstConstraintRow];

  // Keep track of where start time variables are; ignore slack variables.
  if (nonBasicVar < startTimeLocations.size())
    startTimeLocations[nonBasicVar] = -pivotRow; // ...going into basis.
  if (basicVar < startTimeLocations.size())
    startTimeLocations[basicVar] = pivotColumn; // ...going out of basis.

  // Record the swap in the variable lists.
  std::swap(nonBasicVar, basicVar);
}

LogicalResult SimplexSchedulerBase::solveTableau() {
  // "Solving" technically means perfoming dual pivot steps until primal
  // feasibility is reached, i.e. the parametric constants in all constraint
  // rows are non-negative.
  while (auto pivotRow = findDualPivotRow()) {
    // Look for pivot elements.
    if (auto pivotCol = findDualPivotColumn(*pivotRow)) {
      pivot(*pivotRow, *pivotCol);
      continue;
    }

    // If we did not find a pivot column, then the entire row contained only
    // positive entries, and the problem is in principle infeasible. However, if
    // the entry in the `parameterTColumn` is positive, we can try to make the
    // LP feasible again by increasing the II.
    int entry1Col = tableau[*pivotRow][parameter1Column];
    int entryTCol = tableau[*pivotRow][parameterTColumn];
    if (entryTCol > 0) {
      // The negation of `entry1Col` is not in the paper. I think this is an
      // oversight, because `entry1Col` certainly is negative (otherwise the row
      // would not have been a valid pivot row), and without the negation, the
      // new II would be negative.
      // A row whose constant entry is not negative cannot be repaired by a
      // larger II: report the program as infeasible instead of asserting
      // (hls-est OPEN_ISSUES O9 / O208: 21 held-out Vitis_Libraries aes
      // designs reached it; the caller falls back as for any infeasible
      // problem).
      if (entry1Col >= 0)
        return failure();
      int newParameterT = (-entry1Col - 1) / entryTCol + 1;
      if (newParameterT > parameterT) {
        parameterT = newParameterT;
        LLVM_DEBUG(dbgs() << "Increased II to " << parameterT << '\n');
        continue;
      }
    }

    // Otherwise, the linear program is infeasible.
    return failure();
  }

  // Optimal solution found!
  return success();
}

LogicalResult SimplexSchedulerBase::restoreDualFeasibility() {
  // Dual feasibility requires that all columns in the cost matrix are
  // non-lexico-negative. This property may be violated after changing the order
  // of the objective rows, and can be restored by performing primal pivot
  // steps.
  while (auto pivotCol = findPrimalPivotColumn()) {
    // Look for pivot elements.
    if (auto pivotRow = findPrimalPivotRow(*pivotCol)) {
      pivot(*pivotRow, *pivotCol);
      continue;
    }

    // Otherwise, the linear program is unbounded.
    return failure();
  }

  // Optimal solution found!
  return success();
}

bool SimplexSchedulerBase::isInBasis(unsigned startTimeVariable) {
  assert(startTimeVariable < startTimeLocations.size());
  int loc = startTimeLocations[startTimeVariable];
  if (-loc >= (int)firstConstraintRow)
    return true;
  if (loc >= (int)firstNonBasicVariableColumn)
    return false;
  llvm_unreachable("Invalid variable location");
}

std::optional<unsigned>
SimplexSchedulerBase::freeze(unsigned startTimeVariable, unsigned timeStep) {
  assert(startTimeVariable < startTimeLocations.size());
  assert(!frozenVariables.count(startTimeVariable));

  // Mark variable.
  frozenVariables[startTimeVariable] = timeStep;
  frozenFlags[startTimeVariable] = 1;

  if (!isInBasis(startTimeVariable))
    // That's all for non-basic variables.
    return startTimeLocations[startTimeVariable];

  // We need to pivot this variable one out of basis.
  unsigned pivotRow = -startTimeLocations[startTimeVariable];

  // Here, positive pivot elements can be considered as well, hence finding a
  // suitable column should not fail. MODIFIED (hls-est T7, OPEN_ISSUES O9):
  // if it does (an assertion before), undo the mark and report that the
  // variable cannot be fixed; the tableau is unchanged.
  auto pivotCol = findDualPivotColumn(pivotRow, /* allowPositive= */ true);
  if (!pivotCol) {
    frozenVariables.erase(startTimeVariable);
    frozenFlags[startTimeVariable] = 0;
    return std::nullopt;
  }

  // Perform the exchange.
  pivot(pivotRow, *pivotCol);

  // `startTimeVariable` is now represented by `pivotCol`.
  return *pivotCol;
}

void SimplexSchedulerBase::translate(unsigned column, int factor1, int factorS,
                                     int factorT) {
  forEachNonZeroRow(column, [&](unsigned row) {
    int *rowVec = tableau.rowData(row);
    int elem = rowVec[column];

    rowVec[parameter1Column] += -elem * factor1;
    rowVec[parameterSColumn] += -elem * factorS;
    rowVec[parameterTColumn] += -elem * factorT;
  });
}

LogicalResult SimplexSchedulerBase::scheduleAt(unsigned startTimeVariable,
                                               unsigned timeStep) {
  assert(startTimeVariable < startTimeLocations.size());
  assert(!frozenVariables.count(startTimeVariable));

  // Freeze variable and translate its column by parameter S.
  std::optional<unsigned> maybeFrozenCol = freeze(startTimeVariable, timeStep);
  if (!maybeFrozenCol)
    return failure();
  unsigned frozenCol = *maybeFrozenCol;
  translate(frozenCol, /* factor1= */ 0, /* factorS= */ 1, /* factorT= */ 0);

  // Temporarily set S to the desired value, and attempt to solve.
  parameterS = timeStep;
  auto solved = solveTableau();
  parameterS = 0;

  if (failed(solved)) {
    // The LP is infeasible with the new constraint. We could try other values
    // for S, but for now, we just roll back and signal failure to the driver.
    translate(frozenCol, /* factor1= */ 0, /* factorS= */ -1, /* factorT= */ 0);
    frozenVariables.erase(startTimeVariable);
    frozenFlags[startTimeVariable] = 0;
    // MODIFIED (hls-est T7, OPEN_ISSUES O9): was an assertion.
    if (failed(solveTableau()))
      tableauInvalid = true;
    return failure();
  }

  // Translate S by the other parameter(s). This means setting `factor1` to
  // `timeStep`.
  //
  // This translation does not change the values of the parametric constants,
  // hence we do not need to solve the tableau again.
  //
  // Note: I added a negation of the factors here, which is not mentioned in the
  // paper's text, but apparently used in the example. Without it, the intended
  // effect, i.e. making the S-column all-zero again, is not achieved.
  //
  // Note 2: For cyclic problems, the paper suggested to perform a modulo
  // decomposition: S = `factor1` + `factorT` * T, with `factor1` < T.
  // However, this makes the value baked into the tableau dependent on
  // `parameterT`, and it is unclear to me how to update it correctly when
  // changing the II. I found it much more robust to fix the operations to
  // absolute time steps, and manually shift them by the appropriate amount
  // whenever the II is incremented (cf. adding `phiJ`, `phiN` in the modulo
  // scheduler's `scheduleOperation` method).
  translate(parameterSColumn, /* factor1= */ -timeStep, /* factorS= */ 1,
            /* factorT= */ 0);

  return success();
}

void SimplexSchedulerBase::moveBy(unsigned startTimeVariable, unsigned amount) {
  assert(startTimeVariable < startTimeLocations.size());
  assert(frozenVariables.count(startTimeVariable));

  // Bookkeeping.
  frozenVariables[startTimeVariable] += amount;

  // Moving an already frozen variable means translating it by the desired
  // amount, and solving the tableau to restore primal feasibility...
  translate(startTimeLocations[startTimeVariable], /* factor1= */ amount,
            /* factorS= */ 0, /* factorT= */ 0);

  // ... however, we typically batch-move multiple operations (otherwise, the
  // tableau may become infeasible on intermediate steps), so actually defer
  // solving to the caller.
}

unsigned SimplexSchedulerBase::getStartTime(unsigned startTimeVariable) {
  assert(startTimeVariable < startTimeLocations.size());

  if (!isInBasis(startTimeVariable))
    // Non-basic variables that are not already fixed to a specific time step
    // are 0 at the end of the simplex algorithm.
    return frozenVariables.lookup(startTimeVariable);

  // For the variables currently in basis, we look up the solution in the
  // tableau.
  return getParametricConstant(-startTimeLocations[startTimeVariable]);
}

void SimplexSchedulerBase::dumpTableau() {
  for (unsigned j = 0; j < nColumns; ++j)
    dbgs() << "====";
  dbgs() << "==\n";
  for (unsigned i = 0; i < nRows; ++i) {
    if (i == firstConstraintRow) {
      for (unsigned j = 0; j < nColumns; ++j) {
        if (j == firstNonBasicVariableColumn)
          dbgs() << "-+";
        dbgs() << "----";
      }
      dbgs() << '\n';
    }
    for (unsigned j = 0; j < nColumns; ++j) {
      if (j == firstNonBasicVariableColumn)
        dbgs() << " |";
      dbgs() << format(" %3d", tableau[i][j]);
    }
    if (i >= firstConstraintRow)
      dbgs() << format(" |< %2d", basicVariables[i - firstConstraintRow]);
    dbgs() << '\n';
  }
  for (unsigned j = 0; j < nColumns; ++j)
    dbgs() << "====";
  dbgs() << "==\n";
  dbgs() << format(" %3d %3d %3d | ", 1, parameterS, parameterT);
  for (unsigned j = firstNonBasicVariableColumn; j < nColumns; ++j)
    dbgs() << format(" %2d^",
                     nonBasicVariables[j - firstNonBasicVariableColumn]);
  dbgs() << '\n';
}

//===----------------------------------------------------------------------===//
// SimplexScheduler
//===----------------------------------------------------------------------===//

LogicalResult SimplexScheduler::schedule() {
  if (failed(checkLastOp()))
    return failure();

  parameterS = 0;
  parameterT = 0;
  buildTableau();

  LLVM_DEBUG(dbgs() << "Initial tableau:\n"; dumpTableau());

  if (failed(solveTableau()))
    return prob.getContainingOp()->emitError() << "problem is infeasible";

  assert(parameterT == 0);
  LLVM_DEBUG(
      dbgs() << "Final tableau:\n"; dumpTableau();
      dbgs() << "Optimal solution found with start time of last operation = "
             << -getParametricConstant(0) << '\n');

  for (auto *op : prob.getOperations())
    prob.setStartTime(op, getStartTime(startTimeVariables[op]));

  return success();
}

//===----------------------------------------------------------------------===//
// CyclicSimplexScheduler
//===----------------------------------------------------------------------===//

void CyclicSimplexScheduler::fillConstraintRow(SmallVector<int> &row,
                                               Problem::Dependence dep) {
  SimplexSchedulerBase::fillConstraintRow(row, dep);
  if (auto dist = prob.getDistance(dep))
    row[parameterTColumn] = *dist;
}

LogicalResult CyclicSimplexScheduler::schedule() {
  if (failed(checkLastOp()))
    return failure();

  parameterS = 0;
  parameterT = 1;
  buildTableau();

  LLVM_DEBUG(dbgs() << "Initial tableau:\n"; dumpTableau());

  if (failed(solveTableau()))
    return prob.getContainingOp()->emitError() << "problem is infeasible";

  LLVM_DEBUG(dbgs() << "Final tableau:\n"; dumpTableau();
             dbgs() << "Optimal solution found with II = " << parameterT
                    << " and start time of last operation = "
                    << -getParametricConstant(0) << '\n');

  prob.setInitiationInterval(parameterT);
  for (auto *op : prob.getOperations())
    prob.setStartTime(op, getStartTime(startTimeVariables[op]));

  return success();
}

//===----------------------------------------------------------------------===//
// SharedOperatorsSimplexScheduler
//===----------------------------------------------------------------------===//

static bool isLimited(Operation *op, SharedOperatorsProblem &prob) {
  auto maybeRsrcs = prob.getLinkedResourceTypes(op);
  if (!maybeRsrcs)
    return false;
  return llvm::any_of(*maybeRsrcs, [&](Problem::ResourceType rsrc) {
    return prob.getLimit(rsrc).value_or(0) > 0;
  });
}

LogicalResult SharedOperatorsSimplexScheduler::schedule() {
  if (failed(checkLastOp()))
    return failure();

  parameterS = 0;
  parameterT = 0;
  buildTableau();

  LLVM_DEBUG(dbgs() << "Initial tableau:\n"; dumpTableau());

  if (failed(solveTableau()))
    return prob.getContainingOp()->emitError() << "problem is infeasible";

  LLVM_DEBUG(dbgs() << "After solving resource-free problem:\n"; dumpTableau());

  // The *heuristic* part of this scheduler starts here:
  // We will now *choose* start times for operations using a shared operator
  // type, in a way that respects the allocation limits, and consecutively solve
  // the LP with these added constraints. The individual LPs are still solved to
  // optimality (meaning: the start times of the "last" operation is still
  // optimal w.r.t. the already fixed operations), however the heuristic choice
  // means we cannot guarantee the optimality for the overall problem.

  // Determine which operations are subject to resource constraints.
  auto &ops = prob.getOperations();
  SmallVector<Operation *> limitedOps;
  for (auto *op : ops)
    if (isLimited(op, prob))
      limitedOps.push_back(op);

  // Build a priority list of the limited operations.
  //
  // We sort by the resource-free start times to produce a topological order of
  // the operations. Better priority functions are known, but require computing
  // additional properties, e.g. ASAP and ALAP times for mobility, or graph
  // analysis for height. Assigning operators (=resources) in this order at
  // least ensures that the (acyclic!) problem remains feasible throughout the
  // process.
  //
  // TODO: Implement more sophisticated priority function.
  std::stable_sort(limitedOps.begin(), limitedOps.end(),
                   [&](Operation *a, Operation *b) {
                     return getStartTime(startTimeVariables[a]) <
                            getStartTime(startTimeVariables[b]);
                   });

  // Store the number of operations using a resource type in a particular time
  // step.
  SmallDenseMap<Problem::ResourceType, SmallDenseMap<unsigned, unsigned>>
      reservationTable;

  for (auto *op : limitedOps) {
    auto maybeRsrcs = prob.getLinkedResourceTypes(op);
    assert(maybeRsrcs && "Limited operation must have linked resource types");

    // MODIFIED (hls-est W9r11 review D4): an operation may hold one unit of
    // several resource types; it needs a time step where each has room.
    SmallVector<std::pair<Problem::ResourceType, unsigned>, 2> limited;
    for (auto rsrc : *maybeRsrcs)
      if (unsigned limit = prob.getLimit(rsrc).value_or(0))
        limited.push_back({rsrc, limit});
    assert(!limited.empty());

    // Find the first time step (beginning at the current start time in the
    // partial schedule) in which an operator instance is available.
    unsigned startTimeVar = startTimeVariables[op];
    unsigned candTime = getStartTime(startTimeVar);
    while (llvm::any_of(limited, [&](auto &rl) {
      return reservationTable[rl.first].lookup(candTime) == rl.second;
    }))
      ++candTime;

    // Fix the start time. As explained above, this cannot make the problem
    // infeasible.
    auto fixed = scheduleAt(startTimeVar, candTime);
    assert(succeeded(fixed));
    (void)fixed;

    // Record the operator use.
    for (auto &rl : limited)
      ++reservationTable[rl.first][candTime];

    LLVM_DEBUG(dbgs() << "After scheduling " << startTimeVar
                      << " to t=" << candTime << ":\n";
               dumpTableau());
  }

  assert(parameterT == 0);
  LLVM_DEBUG(
      dbgs() << "Final tableau:\n"; dumpTableau();
      dbgs() << "Feasible solution found with start time of last operation = "
             << -getParametricConstant(0) << '\n');

  for (auto *op : ops)
    prob.setStartTime(op, getStartTime(startTimeVariables[op]));

  return success();
}

//===----------------------------------------------------------------------===//
// ModuloSimplexScheduler
//===----------------------------------------------------------------------===//

LogicalResult ModuloSimplexScheduler::checkLastOp() {
  auto *contOp = prob.getContainingOp();
  if (!prob.hasOperation(lastOp))
    return contOp->emitError("problem does not include last operation");

  // Determine which operations have no outgoing *intra*-iteration dependences.
  auto &ops = prob.getOperations();
  DenseSet<Operation *> sinks(ops.begin(), ops.end());
  for (auto *op : ops)
    for (auto &dep : prob.getDependences(op))
      if (prob.getDistance(dep).value_or(0) == 0)
        sinks.erase(dep.getSource());

  if (!sinks.contains(lastOp))
    return contOp->emitError("last operation is not a sink");
  if (sinks.size() > 1)
    return contOp->emitError("multiple sinks detected");

  return success();
}

// MODIFIED (hls-est W9r11 review D4): an operation may hold one unit of
// several resource types in its slot (an access of a partitioned argument
// whose bank is not a constant takes a port of every bank, VITIS_NOTES N88);
// it enters only when every limited one has room in that slot.
LogicalResult ModuloSimplexScheduler::MRT::enter(Operation *op,
                                                 unsigned timeStep) {
  auto maybeRsrcs = sched.prob.getLinkedResourceTypes(op);
  assert(maybeRsrcs && "Operation must have linked resource types");

  SmallVector<Problem::ResourceType, 2> limited;
  for (auto rsrc : *maybeRsrcs)
    if (sched.prob.getLimit(rsrc).value_or(0) > 0)
      limited.push_back(rsrc);
  assert(!limited.empty());

  unsigned slot = timeStep % sched.parameterT;
  for (auto rsrc : limited) {
    assert(!reverseTables[rsrc].count(op));
    if (tables[rsrc][slot].size() >= *sched.prob.getLimit(rsrc))
      return failure();
  }
  for (auto rsrc : limited) {
    tables[rsrc][slot].insert(op);
    reverseTables[rsrc][op] = slot;
  }
  return success();
}

void ModuloSimplexScheduler::MRT::release(Operation *op) {
  auto maybeRsrcs = sched.prob.getLinkedResourceTypes(op);
  assert(maybeRsrcs && "Operation must have linked resource types");

  for (auto rsrc : *maybeRsrcs) {
    if (sched.prob.getLimit(rsrc).value_or(0) == 0)
      continue;
    auto &revTab = reverseTables[rsrc];
    auto it = revTab.find(op);
    assert(it != revTab.end());
    tables[rsrc][it->second].erase(op);
    revTab.erase(it);
  }
}

bool ModuloSimplexScheduler::fillObjectiveRow(SmallVector<int> &row,
                                              unsigned obj) {
  switch (obj) {
  case OBJ_LATENCY:
    // Minimize start time of user-specified last operation.
    row[startTimeLocations[startTimeVariables[lastOp]]] = 1;
    return true;
  case OBJ_AXAP:
    // Minimize sum of start times of all-but-the-last operation.
    for (auto *op : getProblem().getOperations())
      if (op != lastOp)
        row[startTimeLocations[startTimeVariables[op]]] = 1;
    return false;
  default:
    llvm_unreachable("Unsupported objective requested");
  }
}

LogicalResult ModuloSimplexScheduler::updateMargins() {
  // Assumption: current secondary objective is "ASAP".
  // Negate the objective row once to effectively maximize the sum of start
  // times, which yields the "ALAP" times after solving the tableau. Then,
  // negate it again to restore the "ASAP" objective, and store these times as
  // well.
  for (auto *axapTimes : {&alapTimes, &asapTimes}) {
    multiplyRow(OBJ_AXAP, -1);
    // This should not fail for a feasible tableau. MODIFIED (hls-est T4,
    // OPEN_ISSUES O9): report a failure instead of asserting, so that a
    // caller can fall back to another scheduler.
    auto dualFeasRestored = restoreDualFeasibility();
    auto solved = solveTableau();
    if (failed(dualFeasRestored) || failed(solved))
      return failure();

    for (unsigned stv = 0; stv < startTimeLocations.size(); ++stv)
      (*axapTimes)[stv] = getStartTime(stv);
  }
  return success();
}

LogicalResult ModuloSimplexScheduler::scheduleOperation(Operation *n) {
  auto oprN = *prob.getLinkedOperatorType(n);
  unsigned stvN = startTimeVariables[n];

  // Get current state of the LP. We'll try to schedule at its current time step
  // in the partial solution, and the II-1 following time steps. Scheduling the
  // op to a later time step may increase the overall latency, however, as long
  // as the solution is still feasible, we prefer that over incrementing the II
  // to resolve resource conflicts.
  unsigned stN = getStartTime(stvN);
  unsigned ubN = stN + parameterT - 1;

  LLVM_DEBUG(dbgs() << "Attempting to schedule in [" << stN << ", " << ubN
                    << "]: " << *n << '\n');

  for (unsigned ct = stN; ct <= ubN; ++ct)
    if (succeeded(mrt.enter(n, ct))) {
      auto fixedN = scheduleAt(stvN, ct);
      if (succeeded(fixedN)) {
        LLVM_DEBUG(dbgs() << "Success at t=" << ct << " " << *n << '\n');
        return success();
      }
      // Problem became infeasible with `n` at `ct`, roll back the MRT
      // assignment. Also, no later time can be feasible, so stop the search
      // here.
      mrt.release(n);
      break;
    }
  // MODIFIED (hls-est T7, OPEN_ISSUES O9): the rollback left no feasible
  // tableau.
  if (tableauInvalid)
    return failure();

  // As a last resort, increase II to make room for the op. De Dinechin's
  // Theorem 1 lays out conditions/guidelines to transform the current partial
  // schedule for II to a valid one for a larger II'.

  LLVM_DEBUG(dbgs() << "Incrementing II to " << (parameterT + 1)
                    << " to resolve resource conflict for " << *n << '\n');

  // Note that the approach below is much simpler than in the paper
  // because of the fully-pipelined operators. In our case, it's always
  // sufficient to increment the II by one.

  // Decompose start time.
  unsigned phiN = stN / parameterT;
  unsigned tauN = stN % parameterT;

  // Keep track whether the following moves free at least one operator
  // instance in the slot desired by the current op - then it can stay there.
  unsigned deltaN = 1;

  // We're going to revisit the current partial schedule.
  SmallVector<Operation *> moved;
  for (Operation *j : scheduled) {
    auto oprJ = *prob.getLinkedOperatorType(j);
    unsigned stvJ = startTimeVariables[j];
    unsigned stJ = getStartTime(stvJ);
    unsigned phiJ = stJ / parameterT;
    unsigned tauJ = stJ % parameterT;
    unsigned deltaJ = 0;

    if (oprN == oprJ) {
      // To actually resolve the resource conflicts, we will move operations
      // that are "preceded" (cf. de Dinechin's ≺ relation) one slot to the
      // right.
      if (tauN < tauJ || (tauN == tauJ && phiN > phiJ) ||
          (tauN == tauJ && phiN == phiJ && stvN < stvJ)) {
        // TODO: Replace the last condition with a proper graph analysis.

        deltaJ = 1;
        moved.push_back(j);
        if (tauN == tauJ)
          deltaN = 0;
      }
    }

    // Move operation.
    //
    // In order to keep the op in its current MRT slot `tauJ` after incrementing
    // the II, we add `phiJ`:
    //   stJ + phiJ = (phiJ * parameterT + tauJ) + phiJ
    //              = phiJ * (parameterT + 1) + tauJ
    //
    // Shifting an additional `deltaJ` time steps then moves the op to a
    // different MRT slot, in order to make room for the operation that caused
    // the resource conflict.
    moveBy(stvJ, phiJ + deltaJ);
  }

  // Finally, increment the II and solve to apply the moves. MODIFIED (hls-est
  // T4, OPEN_ISSUES O9): the II bump can leave an infeasible tableau (seen on
  // machsuite fft_transpose and on unrolled bodies with data-dependent ifs);
  // report it instead of asserting.
  ++parameterT;
  auto solved = solveTableau();
  if (failed(solved))
    return failure();

  // Re-enter moved operations into their new slots.
  for (auto *m : moved)
    mrt.release(m);
  for (auto *m : moved) {
    auto enteredM = mrt.enter(m, getStartTime(startTimeVariables[m]));
    if (failed(enteredM))
      return failure();
  }

  // Finally, schedule the operation. Again, adding `phiN` accounts for the
  // implicit shift caused by incrementing the II.
  auto fixedN = scheduleAt(stvN, stN + phiN + deltaN);
  auto enteredN = mrt.enter(n, tauN + deltaN);
  if (failed(fixedN) || failed(enteredN))
    return failure();
  return success();
}

unsigned ModuloSimplexScheduler::computeResMinII() {
  unsigned resMinII = 1;
  SmallDenseMap<Problem::ResourceType, unsigned> uses;
  for (auto *op : prob.getOperations()) {
    auto maybeRsrcs = prob.getLinkedResourceTypes(op);
    if (!maybeRsrcs)
      continue;

    for (auto rsrc : *maybeRsrcs) {
      if (prob.getLimit(rsrc).value_or(0) > 0)
        ++uses[rsrc];
    }
  }

  for (auto pair : uses)
    resMinII = std::max(
        resMinII, (unsigned)ceil(pair.second / *prob.getLimit(pair.first)));

  return resMinII;
}

LogicalResult ModuloSimplexScheduler::schedule() {
  if (failed(checkLastOp()))
    return failure();

  parameterS = 0;
  parameterT = computeResMinII();
  LLVM_DEBUG(dbgs() << "ResMinII = " << parameterT << "\n");
  buildTableau();
  asapTimes.resize(startTimeLocations.size());
  alapTimes.resize(startTimeLocations.size());

  LLVM_DEBUG(dbgs() << "Initial tableau:\n"; dumpTableau());

  if (failed(solveTableau()))
    return prob.getContainingOp()->emitError() << "problem is infeasible";

  // Determine which operations are subject to resource constraints.
  auto &ops = prob.getOperations();
  for (auto *op : ops)
    if (isLimited(op, prob))
      unscheduled.push_back(op);

  // Main loop: Iteratively fix limited operations to time steps.
  while (!unscheduled.empty()) {
    // Update ASAP/ALAP times.
    if (failed(updateMargins()))
      return failure();

    // Heuristically (here: least amount of slack) pick the next operation to
    // schedule.
    auto *opIt =
        std::min_element(unscheduled.begin(), unscheduled.end(),
                         [&](Operation *opA, Operation *opB) {
                           auto stvA = startTimeVariables[opA];
                           auto stvB = startTimeVariables[opB];
                           auto slackA = alapTimes[stvA] - asapTimes[stvA];
                           auto slackB = alapTimes[stvB] - asapTimes[stvB];
                           return slackA < slackB;
                         });
    Operation *op = *opIt;
    unscheduled.erase(opIt);

    if (failed(scheduleOperation(op)))
      return failure();
    scheduled.push_back(op);
  }

  LLVM_DEBUG(dbgs() << "Final tableau:\n"; dumpTableau();
             dbgs() << "Solution found with II = " << parameterT
                    << " and start time of last operation = "
                    << -getParametricConstant(0) << '\n');

  prob.setInitiationInterval(parameterT);
  for (auto *op : ops)
    prob.setStartTime(op, getStartTime(startTimeVariables[op]));

  return success();
}

//===----------------------------------------------------------------------===//
// ChainingSimplexScheduler
//===----------------------------------------------------------------------===//

void ChainingSimplexScheduler::fillAdditionalConstraintRow(
    SmallVector<int> &row, Problem::Dependence dep) {
  fillConstraintRow(row, dep);
  // One _extra_ time step breaks the chain (note that the latency is negative
  // in the tableau).
  row[parameter1Column] -= 1;
}

LogicalResult ChainingSimplexScheduler::schedule() {
  if (failed(checkLastOp()) || failed(computeChainBreakingDependences(
                                   prob, cycleTime, additionalConstraints)))
    return failure();

  parameterS = 0;
  parameterT = 0;
  buildTableau();

  LLVM_DEBUG(dbgs() << "Initial tableau:\n"; dumpTableau());

  if (failed(solveTableau()))
    return prob.getContainingOp()->emitError() << "problem is infeasible";

  assert(parameterT == 0);
  LLVM_DEBUG(
      dbgs() << "Final tableau:\n"; dumpTableau();
      dbgs() << "Optimal solution found with start time of last operation = "
             << -getParametricConstant(0) << '\n');

  for (auto *op : prob.getOperations())
    prob.setStartTime(op, getStartTime(startTimeVariables[op]));

  auto filledIn = computeStartTimesInCycle(prob);
  assert(succeeded(filledIn)); // Problem is known to be acyclic at this point.
  (void)filledIn;

  return success();
}

//===----------------------------------------------------------------------===//
// ChainingCyclicSimplexScheduler
//===----------------------------------------------------------------------===//

void ChainingCyclicSimplexScheduler::fillConstraintRow(
    SmallVector<int> &row, Problem::Dependence dep) {
  SimplexSchedulerBase::fillConstraintRow(row, dep);
  if (auto dist = prob.getDistance(dep))
    row[parameterTColumn] = *dist;
}

void ChainingCyclicSimplexScheduler::fillAdditionalConstraintRow(
    SmallVector<int> &row, Problem::Dependence dep) {
  fillConstraintRow(row, dep);
  // One _extra_ time step breaks the chain (note that the latency is negative
  // in the tableau).
  row[parameter1Column] -= 1;
}

LogicalResult ChainingCyclicSimplexScheduler::schedule() {
  if (failed(checkLastOp()) || failed(computeChainBreakingDependences(
                                   prob, cycleTime, additionalConstraints)))
    return failure();

  parameterS = 0;
  parameterT = 1;
  buildTableau();

  LLVM_DEBUG(dbgs() << "Initial tableau:\n"; dumpTableau());

  if (failed(solveTableau()))
    return prob.getContainingOp()->emitError() << "problem is infeasible";

  LLVM_DEBUG(dbgs() << "Final tableau:\n"; dumpTableau();
             dbgs() << "Optimal solution found with II = " << parameterT
                    << " and start time of last operation = "
                    << -getParametricConstant(0) << '\n');

  prob.setInitiationInterval(parameterT);
  for (auto *op : prob.getOperations())
    prob.setStartTime(op, getStartTime(startTimeVariables[op]));

  auto filledIn = computeStartTimesInCycle(prob);
  assert(succeeded(filledIn));
  (void)filledIn;

  return success();
}

//===----------------------------------------------------------------------===//
// Public API
//===----------------------------------------------------------------------===//

LogicalResult scheduling::scheduleSimplex(Problem &prob, Operation *lastOp) {
  SimplexScheduler simplex(prob, lastOp);
  return simplex.schedule();
}

LogicalResult scheduling::scheduleSimplex(CyclicProblem &prob,
                                          Operation *lastOp) {
  CyclicSimplexScheduler simplex(prob, lastOp);
  return simplex.schedule();
}

LogicalResult scheduling::scheduleSimplex(SharedOperatorsProblem &prob,
                                          Operation *lastOp) {
  SharedOperatorsSimplexScheduler simplex(prob, lastOp);
  return simplex.schedule();
}

LogicalResult scheduling::scheduleSimplex(ModuloProblem &prob,
                                          Operation *lastOp) {
  ModuloSimplexScheduler simplex(prob, lastOp);
  return simplex.schedule();
}

LogicalResult scheduling::scheduleSimplex(ChainingProblem &prob,
                                          Operation *lastOp, float cycleTime) {
  ChainingSimplexScheduler simplex(prob, lastOp, cycleTime);
  return simplex.schedule();
}

LogicalResult scheduling::scheduleSimplex(ChainingCyclicProblem &prob,
                                          Operation *lastOp, float cycleTime) {
  ChainingCyclicSimplexScheduler simplex(prob, lastOp, cycleTime);
  return simplex.schedule();
}
