//
// Created by ebaup on 06.12.24.
//

#ifndef IMPLICITSOLVER_H
#define IMPLICITSOLVER_H
#include "AbstractOdeSolver.h"
#include "utils.h"

class ImplicitSolver : public AbstractOdeSolver {
public:
    using AbstractOdeSolver::AbstractOdeSolver;
protected:
    virtual double step(double y, double t) = 0;
    double newton(double yn, double tn1);
};
#endif //IMPLICITSOLVER_H
