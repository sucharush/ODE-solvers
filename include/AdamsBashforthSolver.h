/**
 * @file AdamsBashforthSolver.h
 * @brief Header file for the Adams-Bashforth solvers.
 * @author csy
 * @date 03.12.24.
 */
#ifndef ADAMSBASHFORTHSOLVER_H
#define ADAMSBASHFORTHSOLVER_H

#include "ExplicitMultiStepSolver.h"

//! Class for Adams-Bashforth solvers

class AdamsBashforthSolver: public ExplicitMultiStepSolver {
public:
    /// Constructor
    /*!
    This constructor sets the order and initial method of an explicit multi-step solver with the parent's constructor,
    and initialize the coefficients associated with the solver (weights).
    @param steps order of the solver
    @param initMethod initial method to compute the initial values
    @see ExplicitMultiStepSolver::ExplicitMultiStepSolver
    */
    AdamsBashforthSolver(int steps, const std::string &initMethod);
    // Simple destructor
    virtual ~AdamsBashforthSolver();
protected:
    virtual double step(double y, double t) override;
    /// Auxiliary method to set up the coefficients associated with the solver.
    void SetCoeffs();
};
#endif //ADAMSBASHFORTHSOLVER_H
