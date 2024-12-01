//
// Created by csy on 2024/11/22.
//

#ifndef FORWARDEULERSOLVER_H
#define FORWARDEULERSOLVER_H

#include "AbstractOdeSolver.h"

class ForwardEulerSolver : public AbstractOdeSolver {
  public:
    ForwardEulerSolver();
    virtual ~ForwardEulerSolver();
  protected:
    virtual double step(double y, double t);
};
#endif //FORWARDEULERSOLVER_H
