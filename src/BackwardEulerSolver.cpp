//
// Created by ebaup on 29.11.24.
//
#include "BackwardEulerSolver.h"

double BackwardEulerSolver::step(double yn, double tn1){
    FuncType Fn(
        [&tn1](double x) { return x - yn - stepSize*f_rhs->value(x, tn1); }
    );
    DFuncType Dfn(
        [&tn1](double x) { return 1 - stepSize*f_rhs->derivative(x, tn1); }
        );

    return newton(Fn, Dfn, yn);
}

double BackwardEulerSolver::newton(FuncType Fn, DfuncType DFn, double yn, double tn1, int maxiter, double tol){
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