

// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

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
  SmallVector<SmallVector<int>> tableau;

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

  /// Number of rows in the tableau = |obj| + |deps|.
  unsigned nRows;
  /// Number of explicitly stored columns in the tableau = |params| + |ops|.
  unsigned nColumns;

  unsigned nObjectives;
  /// All other rows encode linear constraints.
  unsigned &firstConstraintRow = nObjectives;

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
  std::optional<unsigned> freeze(unsigned startTimeVariable, unsigned timeStep);
  void translate(unsigned column, int factor1, int factorS, int factorT);
  LogicalResult scheduleAt(unsigned startTimeVariable, unsigned timeStep);
  void moveBy(unsigned startTimeVariable, unsigned amount);
  unsigned getStartTime(unsigned startTimeVariable);

  void dumpTableau();

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
  enum { OBJ_LATENCY = 0, OBJ_AXAP };
  bool fillObjectiveRow(SmallVector<int> &row, unsigned obj) override;
  LogicalResult updateMargins();
  LogicalResult scheduleOperation(Operation *elementCount);
  unsigned computeResMinII();

public:
  ModuloSimplexScheduler(ModuloProblem &prob, Operation *lastOp)
      : CyclicSimplexScheduler(prob, lastOp), prob(prob), mrt(*this) {}
  LogicalResult schedule() override;
};

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

} // namespace

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

  row[startTimeLocations[startTimeVariables[lastOp]]] = 1;
  return false;
}

void SimplexSchedulerBase::fillConstraintRow(SmallVector<int> &row,
                                             Problem::Dependence dep) {
  auto &prob = getProblem();
  Operation *src = dep.getSource();
  Operation *dst = dep.getDestination();
  unsigned latency = *prob.getLatency(*prob.getLinkedOperatorType(src));
  row[parameter1Column] = -latency;
  if (src != dst) {
    row[startTimeLocations[startTimeVariables[src]]] = 1;
    row[startTimeLocations[startTimeVariables[dst]]] = -1;
  }
}

void SimplexSchedulerBase::fillAdditionalConstraintRow(
    SmallVector<int> &row, Problem::Dependence dep) {

  (void)row;
  (void)dep;
}

void SimplexSchedulerBase::buildTableau() {
  auto &prob = getProblem();

  unsigned var = 0;

  for (auto *op : prob.getOperations()) {
    nonBasicVariables.push_back(var);
    startTimeVariables[op] = var;
    startTimeLocations.push_back(firstNonBasicVariableColumn + var);
    ++var;
  }

  nColumns = nParameters + nonBasicVariables.size();

  auto addRow = [&]() -> SmallVector<int> & {
    implicitBasicVariableColumnVector.push_back(0);
    return tableau.emplace_back(nColumns, 0);
  };

  nObjectives = 0;
  bool hasMoreObjectives;
  do {
    auto &objRowVec = addRow();
    hasMoreObjectives = fillObjectiveRow(objRowVec, nObjectives);
    ++nObjectives;
  } while (hasMoreObjectives);

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

  nRows = tableau.size();
}

int SimplexSchedulerBase::getParametricConstant(unsigned row) {
  auto &rowVec = tableau[row];

  return rowVec[parameter1Column] + rowVec[parameterSColumn] * parameterS +
         rowVec[parameterTColumn] * parameterT;
}

SmallVector<int> SimplexSchedulerBase::getObjectiveVector(unsigned column) {
  SmallVector<int> objVec;

  for (unsigned obj = 0; obj < nObjectives; ++obj)
    objVec.push_back(tableau[obj][column]);
  return objVec;
}

std::optional<unsigned> SimplexSchedulerBase::findDualPivotRow() {

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

  for (unsigned col = firstNonBasicVariableColumn; col < nColumns; ++col) {
    if (frozenVariables.count(
            nonBasicVariables[col - firstNonBasicVariableColumn]))
      continue;

    int pivotCand = tableau[pivotRow][col];

    if (pivotCand < 0 || (allowPositive && pivotCand > 0)) {

      assert(pivotCand * pivotCand == 1);

      SmallVector<int> quot;
      for (unsigned obj = 0; obj < nObjectives; ++obj)
        quot.push_back(tableau[obj][col] / pivotCand);

      if (std::lexicographical_compare(maxQuot.begin(), maxQuot.end(),
                                       quot.begin(), quot.end())) {
        maxQuot = quot;
        pivotCol = col;
      }
    }
  }

  return pivotCol;
}

std::optional<unsigned> SimplexSchedulerBase::findPrimalPivotColumn() {

  SmallVector<int> zeroVec(nObjectives, 0);
  for (unsigned col = firstNonBasicVariableColumn; col < nColumns; ++col) {
    if (frozenVariables.count(
            nonBasicVariables[col - firstNonBasicVariableColumn]))
      continue;

    SmallVector<int> objVec = getObjectiveVector(col);
    if (std::lexicographical_compare(objVec.begin(), objVec.end(),
                                     zeroVec.begin(), zeroVec.end()))
      return col;
  }

  return std::nullopt;
}

std::optional<unsigned>
SimplexSchedulerBase::findPrimalPivotRow(unsigned pivotColumn) {
  int minQuot = std::numeric_limits<int>::max();
  std::optional<unsigned> pivotRow;

  for (unsigned row = firstConstraintRow; row < nRows; ++row) {
    int pivotCand = tableau[row][pivotColumn];
    if (pivotCand > 0) {

      assert(pivotCand == 1);
      int quot = getParametricConstant(row) / pivotCand;
      if (quot < minQuot) {
        minQuot = quot;
        pivotRow = row;
      }
    }
  }

  return pivotRow;
}

void SimplexSchedulerBase::multiplyRow(unsigned row, int factor) {
  assert(factor != 0);
  for (unsigned col = 0; col < nColumns; ++col)
    tableau[row][col] *= factor;

  implicitBasicVariableColumnVector[row] *= factor;
}

void SimplexSchedulerBase::addMultipleOfRow(unsigned sourceRow, int factor,
                                            unsigned targetRow) {
  assert(factor != 0 && sourceRow != targetRow);
  for (unsigned col = 0; col < nColumns; ++col)
    tableau[targetRow][col] += tableau[sourceRow][col] * factor;

  implicitBasicVariableColumnVector[targetRow] +=
      implicitBasicVariableColumnVector[sourceRow] * factor;
}

/// The pivot operation applies elementary row operations to the tableau in
/// order to make the \p pivotColumn (corresponding to a non-basic variable) a
/// unit vector (only the \p pivotRow'th entry is 1). Then, a basis exchange is
/// performed: the non-basic variable is swapped with the basic variable
/// associated with the pivot row.
void SimplexSchedulerBase::pivot(unsigned pivotRow, unsigned pivotColumn) {

  implicitBasicVariableColumnVector[pivotRow] = 1;

  int pivotElem = tableau[pivotRow][pivotColumn];

  assert(pivotElem * pivotElem == 1);

  multiplyRow(pivotRow, 1 / pivotElem);

  for (unsigned row = 0; row < nRows; ++row) {
    if (row == pivotRow)
      continue;

    int elem = tableau[row][pivotColumn];
    if (elem == 0)
      continue;

    addMultipleOfRow(pivotRow, -elem, row);
  }

  for (unsigned row = 0; row < nRows; ++row) {
    tableau[row][pivotColumn] = implicitBasicVariableColumnVector[row];
    implicitBasicVariableColumnVector[row] = 0;
  }

  unsigned &nonBasicVar =
      nonBasicVariables[pivotColumn - firstNonBasicVariableColumn];
  unsigned &basicVar = basicVariables[pivotRow - firstConstraintRow];

  if (nonBasicVar < startTimeLocations.size())
    startTimeLocations[nonBasicVar] = -pivotRow;
  if (basicVar < startTimeLocations.size())
    startTimeLocations[basicVar] = pivotColumn;

  std::swap(nonBasicVar, basicVar);
}

LogicalResult SimplexSchedulerBase::solveTableau() {

  while (auto pivotRow = findDualPivotRow()) {

    if (auto pivotCol = findDualPivotColumn(*pivotRow)) {
      pivot(*pivotRow, *pivotCol);
      continue;
    }

    int entry1Col = tableau[*pivotRow][parameter1Column];
    int entryTCol = tableau[*pivotRow][parameterTColumn];
    if (entryTCol > 0) {

      assert(entry1Col < 0);
      int newParameterT = (-entry1Col - 1) / entryTCol + 1;
      if (newParameterT > parameterT) {
        parameterT = newParameterT;
        LLVM_DEBUG(dbgs() << "Increased II to " << parameterT << '\n');
        continue;
      }
    }

    return failure();
  }

  return success();
}

LogicalResult SimplexSchedulerBase::restoreDualFeasibility() {

  while (auto pivotCol = findPrimalPivotColumn()) {

    if (auto pivotRow = findPrimalPivotRow(*pivotCol)) {
      pivot(*pivotRow, *pivotCol);
      continue;
    }

    return failure();
  }

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

std::optional<unsigned> SimplexSchedulerBase::freeze(unsigned startTimeVariable,
                                                     unsigned timeStep) {
  assert(startTimeVariable < startTimeLocations.size());
  assert(!frozenVariables.count(startTimeVariable));

  frozenVariables[startTimeVariable] = timeStep;

  if (!isInBasis(startTimeVariable))

    return startTimeLocations[startTimeVariable];

  unsigned pivotRow = -startTimeLocations[startTimeVariable];

  auto pivotCol = findDualPivotColumn(pivotRow, true);
  if (!pivotCol) {
    frozenVariables.erase(startTimeVariable);
    return std::nullopt;
  }

  pivot(pivotRow, *pivotCol);

  return *pivotCol;
}

void SimplexSchedulerBase::translate(unsigned column, int factor1, int factorS,
                                     int factorT) {
  for (unsigned row = 0; row < nRows; ++row) {
    auto &rowVec = tableau[row];
    int elem = rowVec[column];
    if (elem == 0)
      continue;

    rowVec[parameter1Column] += -elem * factor1;
    rowVec[parameterSColumn] += -elem * factorS;
    rowVec[parameterTColumn] += -elem * factorT;
  }
}

LogicalResult SimplexSchedulerBase::scheduleAt(unsigned startTimeVariable,
                                               unsigned timeStep) {
  assert(startTimeVariable < startTimeLocations.size());
  assert(!frozenVariables.count(startTimeVariable));

  std::optional<unsigned> maybeFrozenCol = freeze(startTimeVariable, timeStep);
  if (!maybeFrozenCol)
    return failure();
  unsigned frozenCol = *maybeFrozenCol;
  translate(frozenCol, 0, 1, 0);

  parameterS = timeStep;
  auto solved = solveTableau();
  parameterS = 0;

  if (failed(solved)) {

    translate(frozenCol, 0, -1, 0);
    frozenVariables.erase(startTimeVariable);

    if (failed(solveTableau()))
      tableauInvalid = true;
    return failure();
  }

  translate(parameterSColumn, -timeStep, 1, 0);

  return success();
}

void SimplexSchedulerBase::moveBy(unsigned startTimeVariable, unsigned amount) {
  assert(startTimeVariable < startTimeLocations.size());
  assert(frozenVariables.count(startTimeVariable));

  frozenVariables[startTimeVariable] += amount;

  translate(startTimeLocations[startTimeVariable], amount, 0, 0);
}

unsigned SimplexSchedulerBase::getStartTime(unsigned startTimeVariable) {
  assert(startTimeVariable < startTimeLocations.size());

  if (!isInBasis(startTimeVariable))

    return frozenVariables.lookup(startTimeVariable);

  return getParametricConstant(-startTimeLocations[startTimeVariable]);
}

void SimplexSchedulerBase::dumpTableau() {
  for (unsigned innerIndex = 0; innerIndex < nColumns; ++innerIndex)
    dbgs() << "====";
  dbgs() << "==\n";
  for (unsigned loopIndex = 0; loopIndex < nRows; ++loopIndex) {
    if (loopIndex == firstConstraintRow) {
      for (unsigned innerIndex = 0; innerIndex < nColumns; ++innerIndex) {
        if (innerIndex == firstNonBasicVariableColumn)
          dbgs() << "-+";
        dbgs() << "----";
      }
      dbgs() << '\n';
    }
    for (unsigned innerIndex = 0; innerIndex < nColumns; ++innerIndex) {
      if (innerIndex == firstNonBasicVariableColumn)
        dbgs() << " |";
      dbgs() << format(" %3d", tableau[loopIndex][innerIndex]);
    }
    if (loopIndex >= firstConstraintRow)
      dbgs() << format(" |< %2d",
                       basicVariables[loopIndex - firstConstraintRow]);
    dbgs() << '\n';
  }
  for (unsigned innerIndex = 0; innerIndex < nColumns; ++innerIndex)
    dbgs() << "====";
  dbgs() << "==\n";
  dbgs() << format(" %3d %3d %3d | ", 1, parameterS, parameterT);
  for (unsigned innerIndex = firstNonBasicVariableColumn; innerIndex < nColumns;
       ++innerIndex)
    dbgs() << format(
        " %2d^", nonBasicVariables[innerIndex - firstNonBasicVariableColumn]);
  dbgs() << '\n';
}

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

  auto &ops = prob.getOperations();
  SmallVector<Operation *> limitedOps;
  for (auto *op : ops)
    if (isLimited(op, prob))
      limitedOps.push_back(op);

  std::stable_sort(limitedOps.begin(), limitedOps.end(),
                   [&](Operation *arrayValue, Operation *buildPoint) {
                     return getStartTime(startTimeVariables[arrayValue]) <
                            getStartTime(startTimeVariables[buildPoint]);
                   });

  SmallDenseMap<Problem::ResourceType, SmallDenseMap<unsigned, unsigned>>
      reservationTable;

  for (auto *op : limitedOps) {
    auto maybeRsrcs = prob.getLinkedResourceTypes(op);
    assert(maybeRsrcs && "Limited operation must have linked resource types");

    auto &rsrcs = *maybeRsrcs;
    assert(rsrcs.size() == 1 &&
           "Multi-resource operations are not yet supported by this scheduler");

    auto rsrc = rsrcs[0];
    unsigned limit = prob.getLimit(rsrc).value_or(0);
    assert(limit > 0);

    unsigned startTimeVar = startTimeVariables[op];
    unsigned candTime = getStartTime(startTimeVar);
    while (reservationTable[rsrc].lookup(candTime) == limit)
      ++candTime;

    auto fixed = scheduleAt(startTimeVar, candTime);
    assert(succeeded(fixed));
    (void)fixed;

    ++reservationTable[rsrc][candTime];

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

LogicalResult ModuloSimplexScheduler::checkLastOp() {
  auto *contOp = prob.getContainingOp();
  if (!prob.hasOperation(lastOp))
    return contOp->emitError("problem does not include last operation");

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

LogicalResult ModuloSimplexScheduler::MRT::enter(Operation *op,
                                                 unsigned timeStep) {
  auto maybeRsrcs = sched.prob.getLinkedResourceTypes(op);
  assert(maybeRsrcs && "Operation must have linked resource types");

  auto &rsrcs = *maybeRsrcs;
  assert(rsrcs.size() == 1 &&
         "Multi-resource operations are not yet supported by MRT");

  auto rsrc = rsrcs[0];
  auto lim = *sched.prob.getLimit(rsrc);
  assert(lim > 0);

  auto &revTab = reverseTables[rsrc];
  assert(!revTab.count(op));

  unsigned slot = timeStep % sched.parameterT;
  auto &cell = tables[rsrc][slot];
  if (cell.size() < lim) {
    cell.insert(op);
    revTab[op] = slot;
    return success();
  }
  return failure();
}

void ModuloSimplexScheduler::MRT::release(Operation *op) {
  auto maybeRsrcs = sched.prob.getLinkedResourceTypes(op);
  assert(maybeRsrcs && "Operation must have linked resource types");

  auto &rsrcs = *maybeRsrcs;
  assert(rsrcs.size() == 1 &&
         "Multi-resource operations are not yet supported by MRT");

  auto rsrc = rsrcs[0];
  auto &revTab = reverseTables[rsrc];
  auto it = revTab.find(op);
  assert(it != revTab.end());
  tables[rsrc][it->second].erase(op);
  revTab.erase(it);
}

bool ModuloSimplexScheduler::fillObjectiveRow(SmallVector<int> &row,
                                              unsigned obj) {
  switch (obj) {
  case OBJ_LATENCY:

    row[startTimeLocations[startTimeVariables[lastOp]]] = 1;
    return true;
  case OBJ_AXAP:

    for (auto *op : getProblem().getOperations())
      if (op != lastOp)
        row[startTimeLocations[startTimeVariables[op]]] = 1;
    return false;
  default:
    llvm_unreachable("Unsupported objective requested");
  }
}

LogicalResult ModuloSimplexScheduler::updateMargins() {

  for (auto *axapTimes : {&alapTimes, &asapTimes}) {
    multiplyRow(OBJ_AXAP, -1);

    auto dualFeasRestored = restoreDualFeasibility();
    auto solved = solveTableau();
    if (failed(dualFeasRestored) || failed(solved))
      return failure();

    for (unsigned stv = 0; stv < startTimeLocations.size(); ++stv)
      (*axapTimes)[stv] = getStartTime(stv);
  }
  return success();
}

LogicalResult
ModuloSimplexScheduler::scheduleOperation(Operation *elementCount) {
  auto oprN = *prob.getLinkedOperatorType(elementCount);
  unsigned stvN = startTimeVariables[elementCount];

  unsigned stN = getStartTime(stvN);
  unsigned ubN = stN + parameterT - 1;

  LLVM_DEBUG(dbgs() << "Attempting to schedule in [" << stN << ", " << ubN
                    << "]: " << *elementCount << '\n');

  for (unsigned ct = stN; ct <= ubN; ++ct)
    if (succeeded(mrt.enter(elementCount, ct))) {
      auto fixedN = scheduleAt(stvN, ct);
      if (succeeded(fixedN)) {
        LLVM_DEBUG(dbgs() << "Success at t=" << ct << " " << *elementCount
                          << '\n');
        return success();
      }

      mrt.release(elementCount);
      break;
    }

  if (tableauInvalid)
    return failure();

  LLVM_DEBUG(dbgs() << "Incrementing II to " << (parameterT + 1)
                    << " to resolve resource conflict for " << *elementCount
                    << '\n');

  unsigned phiN = stN / parameterT;
  unsigned tauN = stN % parameterT;

  unsigned deltaN = 1;

  SmallVector<Operation *> moved;
  for (Operation *innerIndex : scheduled) {
    auto oprJ = *prob.getLinkedOperatorType(innerIndex);
    unsigned stvJ = startTimeVariables[innerIndex];
    unsigned stJ = getStartTime(stvJ);
    unsigned phiJ = stJ / parameterT;
    unsigned tauJ = stJ % parameterT;
    unsigned deltaJ = 0;

    if (oprN == oprJ) {

      if (tauN < tauJ || (tauN == tauJ && phiN > phiJ) ||
          (tauN == tauJ && phiN == phiJ && stvN < stvJ)) {

        deltaJ = 1;
        moved.push_back(innerIndex);
        if (tauN == tauJ)
          deltaN = 0;
      }
    }

    moveBy(stvJ, phiJ + deltaJ);
  }

  ++parameterT;
  auto solved = solveTableau();
  if (failed(solved))
    return failure();

  for (auto *memoryOp : moved)
    mrt.release(memoryOp);
  for (auto *memoryOp : moved) {
    auto enteredM =
        mrt.enter(memoryOp, getStartTime(startTimeVariables[memoryOp]));
    if (failed(enteredM))
      return failure();
  }

  auto fixedN = scheduleAt(stvN, stN + phiN + deltaN);
  auto enteredN = mrt.enter(elementCount, tauN + deltaN);
  if (failed(fixedN) || failed(enteredN))
    return failure();
  return success();
}

unsigned ModuloSimplexScheduler::computeResMinII() {
  unsigned resMinII = 1;
  SmallDenseMap<Problem::ResourceType, unsigned> symbolUses;
  for (auto *op : prob.getOperations()) {
    auto maybeRsrcs = prob.getLinkedResourceTypes(op);
    if (!maybeRsrcs)
      continue;

    for (auto rsrc : *maybeRsrcs) {
      if (prob.getLimit(rsrc).value_or(0) > 0)
        ++symbolUses[rsrc];
    }
  }

  for (auto pair : symbolUses)
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

  auto &ops = prob.getOperations();
  for (auto *op : ops)
    if (isLimited(op, prob))
      unscheduled.push_back(op);

  while (!unscheduled.empty()) {

    if (failed(updateMargins()))
      return failure();

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

void ChainingSimplexScheduler::fillAdditionalConstraintRow(
    SmallVector<int> &row, Problem::Dependence dep) {
  fillConstraintRow(row, dep);

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
  assert(succeeded(filledIn));
  (void)filledIn;

  return success();
}

void ChainingCyclicSimplexScheduler::fillConstraintRow(
    SmallVector<int> &row, Problem::Dependence dep) {
  SimplexSchedulerBase::fillConstraintRow(row, dep);
  if (auto dist = prob.getDistance(dep))
    row[parameterTColumn] = *dist;
}

void ChainingCyclicSimplexScheduler::fillAdditionalConstraintRow(
    SmallVector<int> &row, Problem::Dependence dep) {
  fillConstraintRow(row, dep);

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
