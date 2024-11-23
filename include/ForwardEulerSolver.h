//
// Created by csy on 2024/11/22.
//
#include "AbstractOdeSolver.h"

#ifndef FORWARDEULERSOLVER_H
#define FORWARDEULERSOLVER_H

class ForwardEulerSolver : public AbstractOdeSolver {
  public:
    ForwardEulerSolver();
    virtual ~ForwardEulerSolver();
  protected:
    virtual double step(double y, double t);
};
#endif //FORWARDEULERSOLVER_H
