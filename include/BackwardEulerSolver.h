//
// Created by ebaup on 29.11.24.
//

#ifndef BACKWARDEULERSOLVER_H
#define BACKWARDEULERSOLVER_H

#include "ImplicitSolver.h"

class BackwardEulerSolver : public ImplicitSolver {
public:
    BackwardEulerSolver() {}
    virtual ~BackwardEulerSolver() {}
protected:
    virtual double step(double y, double t);
};
#endif //BACKWARDEULERSOLVER_H
