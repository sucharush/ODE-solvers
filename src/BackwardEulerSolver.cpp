//
// Created by ebaup on 29.11.24.
//
#include "BackwardEulerSolver.h"
#include "utils.h"

double BackwardEulerSolver::step(double yn, double tn1){

    return newton(yn, tn1);
}

BackwardEulerSolver::BackwardEulerSolver() {};
BackwardEulerSolver::~BackwardEulerSolver() {};