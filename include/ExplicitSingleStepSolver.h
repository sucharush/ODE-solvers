/**
 * @file ExplicitSingleStepSolver.h
 * @brief Explicit single-step solvers.
 * @author csy
 * @date 05.12.24.
 */
#ifndef EXPLICITSINGLESTEPSOLVER_H
#define EXPLICITSINGLESTEPSOLVER_H

#include "ExplicitSolver.h"

//! Class for explicit single-step solvers

class ExplicitSingleStepSolver : public ExplicitSolver {
public:
    /// Parent's constructor is used
    using ExplicitSolver::ExplicitSolver;
protected:
    virtual double step(double y, double t) = 0;
};
#endif //EXPLICITSINGLESTEPSOLVER_H
