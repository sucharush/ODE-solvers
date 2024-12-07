//
// Created by ebaup on 29.11.24.
//

#ifndef BACKWARDEULERSOLVER_H
#define BACKWARDEULERSOLVER_H
#include "ImplicitSolver.h"

class BackwardEulerSolver : public ImplicitSolver {
public:
    BackwardEulerSolver();
    virtual ~BackwardEulerSolver();
    // Setters for the private parameters
    void SetTolerance(double tol);
    void SetMaxIter(double n_max);
    // TODO: do we need getters?
protected:
    virtual double step(double y, double t);
private:
    double tolerance;
    double max_iter;
};
#endif //BACKWARDEULERSOLVER_H
