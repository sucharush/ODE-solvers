/**
 * @file BackwardEulerSolver.h
 * @brief Backward Euler solver.
 * @author ebaup
 * @date 29.11.24.
 */
#ifndef BACKWARDEULERSOLVER_H
#define BACKWARDEULERSOLVER_H

#include "ImplicitSolver.h"

//!  Class for Backward Euler solver

class BackwardEulerSolver : public ImplicitSolver {
public:
    /// Constructor
    /*!
    This constructor is empty as it used the parent's constructor but no new parameter have to be set.
    @see ImplicitSolver::ImplicitSolver()
    */
    BackwardEulerSolver() {}
    /// Simple destructor
    virtual ~BackwardEulerSolver() {}
protected:
    /// Overriden implementation of the computation of one step of the solver.
    virtual double step(double y, double t);
};
#endif //BACKWARDEULERSOLVER_H
