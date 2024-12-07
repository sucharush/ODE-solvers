//
// Created by ebaup on 29.11.24.
//
#include "BackwardEulerSolver.h"
#include "utils.h"

double BackwardEulerSolver::step(double yn, double tn1){

    return newton(yn, tn1);
}

BackwardEulerSolver::BackwardEulerSolver()
    : tolerance(TOL), max_iter(MAX_ITER) {};
BackwardEulerSolver::~BackwardEulerSolver() {};

void BackwardEulerSolver::SetTolerance(double tol) {
    tolerance = tol;
}
void BackwardEulerSolver::SetMaxIter(double n_max) {
    max_iter = n_max;
}