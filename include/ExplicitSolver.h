//
// Created by csy on 2024/12/5.
//
#include "AbstractOdeSolver.h"
#ifndef EXPLICITSOLVER_H
#define EXPLICITSOLVER_H
class ExplicitSolver : public AbstractOdeSolver {
  public:
    using AbstractOdeSolver::AbstractOdeSolver;
   protected:
     virtual double step(double y, double t) = 0;
};
#endif //EXPLICITSOLVER_H
