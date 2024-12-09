//
// Created by ebaup on 06.12.24.
//

#include "ImplicitSolver.h"
#include <cassert>

ImplicitSolver::ImplicitSolver(double tol, double n_max)
    :tolerance(tol), max_iter(n_max) {}

double ImplicitSolver::newton(double yn, double tn1) {
    double err = tolerance + 1;
    int iter = 0;
    double xi = yn;
    while (err > tolerance && iter < max_iter) {
        double gx = xi - yn - GetStepSize()*f_rhs->value(xi, tn1);
        double dgx = 1 - GetStepSize()*f_rhs->derivative(xi, tn1);
        double delta = - gx / dgx;
        xi = xi + delta;
        iter++;
        err = std::abs(delta);
    }
    assert(iter < max_iter);
    return xi;
}

void ImplicitSolver::SetTolerance(double tol) {
    tolerance = tol;
}
void ImplicitSolver::SetMaxIter(double n_max) {
    max_iter = n_max;
}