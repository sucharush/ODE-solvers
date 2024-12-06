//
// Created by ebaup on 29.11.24.
//
#include "BackwardEulerSolver.h"
#include "utils.h"

double BackwardEulerSolver::step(double yn, double tn1){
    // these are local variables, so does not work
    FuncType Fn(
        [&tn1, this, yn](double x) { return x - yn - GetStepSize()*f_rhs->value(x, tn1); }
    );
    DerivativeType Dfn(
        [&tn1, this](double x) { return 1 - GetStepSize()*f_rhs->derivative(x, tn1); }
        );

    return newton(Fn, Dfn, yn, tn1);
}

double BackwardEulerSolver::newton(FuncType Fn, DerivativeType DFn, double yn, double tn1, int maxiter, double tol){
    double err = tol + 1;
    int iter = 0;
    double xi = yn;
    while (err > tol && iter < maxiter){
        double delta = - Fn(xi, tn1) / DFn(xi, tn1);
        xi = xi + delta;
        iter++;
        err = std::abs(delta);
    }
    return xi;
}