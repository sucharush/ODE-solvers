//
// Created by ebaup on 29.11.24.
//

#ifndef BACKWARDEULERSOLVER_H
#define BACKWARDEULERSOLVER_H
#include "AbstractOdeSolver.h"

class BackwardEulerSolver : public AbstractOdeSolver {
public:
    BackwardEulerSolver();
    virtual ~BackwardEulerSolver();
protected:
    virtual double step(double y, double t);
    double newton(FuncType Fn, DfuncType DFn, double yn, double tn1, int maxiter = 20, double tol = 1e-6);

};
#endif //BACKWARDEULERSOLVER_H
