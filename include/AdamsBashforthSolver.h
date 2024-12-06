//
// Created by csy on 2024/12/3.
//
#include "ExplicitMultiStepSolver.h"

#ifndef ADAMSBASHFORTHSOLVER_H
#define ADAMSBASHFORTHSOLVER_H
class AdamsBashforthSolver: public ExplicitMultiStepSolver {
  public:
    AdamsBashforthSolver(int steps, const std::string &initMethod);
    virtual ~AdamsBashforthSolver();
  protected:
    virtual double step(double y, double t) override;
    void SetCoeffs();
};
#endif //ADAMSBASHFORTHSOLVER_H
