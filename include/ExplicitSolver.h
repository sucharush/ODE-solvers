//
// Created by csy on 2024/12/5.
//

#ifndef EXPLICITSOLVER_H
#define EXPLICITSOLVER_H

#include "AbstractOdeSolver.h"

//!  Class for explicit solvers.
/*!
This is the base function class, that allows us to represent a function (together with its derivative).
@note We kept the name ODERightHandSide, but it could have been renamed simply to Function.
*/

class ExplicitSolver : public AbstractOdeSolver {
  public:
    using AbstractOdeSolver::AbstractOdeSolver;
   protected:
     virtual double step(double y, double t) = 0;
};
#endif //EXPLICITSOLVER_H
