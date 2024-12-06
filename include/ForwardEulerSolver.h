//
// Created by csy on 2024/11/22.
//

#ifndef FORWARDEULERSOLVER_H
#define FORWARDEULERSOLVER_H

#include "ExplicitSingleStepSolver.h"

class ForwardEulerSolver : public ExplicitSingleStepSolver {
  public:
    ForwardEulerSolver();
    virtual ~ForwardEulerSolver();
  protected:
    virtual double step(double y, double t);
};
#endif //FORWARDEULERSOLVER_H
