//
// Created by ebaup on 06.12.24.
//

#ifndef IMPLICITSOLVER_H
#define IMPLICITSOLVER_H

#include "AbstractOdeSolver.h"
#include "utils.h"

class ImplicitSolver : public AbstractOdeSolver {
public:
    // Constructor, with default parameters
    ImplicitSolver(double tol = TOL, double n_max = MAX_ITER);
    // Setters for the private parameters
    void SetTolerance(double tol);
    void SetMaxIter(double n_max);
    // TODO: do we need getters?
protected:
    virtual double step(double y, double t) = 0;
    double newton(double yn, double tn1);
private:
    double tolerance;
    double max_iter;
};
#endif //IMPLICITSOLVER_H
