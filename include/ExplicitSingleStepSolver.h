//
// Created by csy on 2024/12/5.
//

#ifndef EXPLICITSINGLESTEPSOLVER_H
#define EXPLICITSINGLESTEPSOLVER_H

#include "ExplicitSolver.h"

class ExplicitSingleStepSolver : public ExplicitSolver {
  public:
    using ExplicitSolver::ExplicitSolver;
  protected:
    virtual double step(double y, double t) = 0;
};
#endif //EXPLICITSINGLESTEPSOLVER_H
