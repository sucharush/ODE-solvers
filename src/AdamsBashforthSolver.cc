//
// Created by csy on 2024/12/3.
//
#include "AdamsBashforthSolver.h"
#include <iostream>

AdamsBashforthSolver::AdamsBashforthSolver(int steps, const std::string &initMethod)
    : ExplicitMultiStepSolver(steps, initMethod) {
    SetCoeffs();  // Set specific coefficients after initializing base class
}
AdamsBashforthSolver::~AdamsBashforthSolver() {}

void AdamsBashforthSolver::SetCoeffs() {
    int steps = getSteps();  // Ensure steps are set before setting coeffs
    if (steps <= 0 || steps > 4) {
        throw std::logic_error("Steps must be set as a positive integer between 1 and 4.");
    }
    coeffs_.resize(steps);  // Resize the coefficient vector to the number of steps
    switch(steps) {
        case 1:
            coeffs_[0] = 1.0;
        break;
        case 2:
            coeffs_ << 3.0 / 2.0, -1.0 / 2.0;
        break;
        case 3:
            coeffs_ << 23.0 / 12.0, -16.0 / 12.0, 5.0 / 12.0;
        break;
        case 4:
            coeffs_ << 55.0 / 24.0, -59.0 / 24.0, 37.0 / 24.0, -9.0 / 24.0;
        break;
        default:
            throw std::invalid_argument("Unsupported step count for Adams-Bashforth coefficients.");
    }
}

double AdamsBashforthSolver::step(double y, double t) {
    if (coeffs_.size() != getSteps()) {
        throw std::logic_error("Coefficients not properly initialized.");
    }
    double sum = 0;
    int currentStep = static_cast<int>((t - initialTime) / GetStepSize());
    for (int i = 0; i < getSteps(); ++i) {
        sum += coeffs_[i] * f_rhs->value(results[currentStep - i], t - i * GetStepSize());
    }
    return y + GetStepSize() * sum;
}