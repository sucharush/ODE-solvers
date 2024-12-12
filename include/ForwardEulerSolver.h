/**
 * @file ForwardEulerSolver.h
 * @brief Forward Euler solver.
 * @author csy
 * @date 22.11.24.
 */
#ifndef FORWARDEULERSOLVER_H
#define FORWARDEULERSOLVER_H

#include "ExplicitSingleStepSolver.h"

//! Class for the Forward Euler solver

class ForwardEulerSolver : public ExplicitSingleStepSolver {
public:
    /// Simple constructor
    ForwardEulerSolver() {}
    /// Simple destructor
    virtual ~ForwardEulerSolver() {}
protected:
    /// Overriden implementation of the computation of one step of the solver.
    virtual double step(double y, double t);
};
#endif //FORWARDEULERSOLVER_H
