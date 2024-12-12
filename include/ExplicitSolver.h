/**
 * @file ExplicitSolver.h
 * @brief Explicit solver class.
 * @author csy
 * @date 05.12.24.
 */
#ifndef EXPLICITSOLVER_H
#define EXPLICITSOLVER_H

#include "AbstractOdeSolver.h"

//!  Class for explicit solvers. It is an abstract class.

class ExplicitSolver : public AbstractOdeSolver {
  public:
    /// Constructor from the parent used
    using AbstractOdeSolver::AbstractOdeSolver;
   protected:
     virtual double step(double y, double t) = 0;
};
#endif //EXPLICITSOLVER_H
