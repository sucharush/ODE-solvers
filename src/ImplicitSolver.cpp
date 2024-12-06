//
// Created by ebaup on 06.12.24.
//

#include "ImplicitSolver.h"
#include <cassert>
double ImplicitSolver::newton(double yn, double tn1){
    double err = TOL + 1;
    int iter = 0;
    double xi = yn;
    while (err > TOL && iter < MAX_ITER) {
        double gx = xi - yn - GetStepSize()*f_rhs->value(xi, tn1);
        double dgx = 1 - GetStepSize()*f_rhs->derivative(xi, tn1);
        double delta = - gx / dgx;
        xi = xi + delta;
        iter++;
        err = std::abs(delta);
    }
    assert(iter < MAX_ITER);
    return xi;
}