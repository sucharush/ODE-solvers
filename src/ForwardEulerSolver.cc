//
// Created by csy on 2024/11/22.
//
#include "AbstractOdeSolver.h"
#include "ForwardEulerSolver.h"

double ForwardEulerSolver::step(double y, double t){
  return y + GetStepSize() * f_rhs->value(y, t);
}