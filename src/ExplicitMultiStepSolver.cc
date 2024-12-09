//
// Created by csy on 2024/12/5.
//
#include "ExplicitMultiStepSolver.h"
#include <Eigen/Dense>
#include <iostream>
#include <iomanip>  // For std::setprecision

ExplicitMultiStepSolver::ExplicitMultiStepSolver(int steps, const std::string &initMethod)
    : steps_(steps), initMethod_(initMethod), coeffs_(Eigen::VectorXd::Zero(steps)) {
    if (initMethod_ != "FE" && initMethod_ != "RK4") {
        throw std::invalid_argument("Initialization method must be 'FE' or 'RK4'.");
    }
}
ExplicitMultiStepSolver::~ExplicitMultiStepSolver() {}

void ExplicitMultiStepSolver::SolveEquation(std::ostream& stream) {
    double initialTime = GetInitialTime();
    double finalTime = GetFinalTime();
    double stepSize = GetStepSize();
    double initialValue = GetInitialValue();
    stream << std::fixed << std::setprecision(5);

    double t = initialTime;
    double y = initialValue;

    int numSteps = static_cast<int>((finalTime - initialTime) / stepSize) + 1;
    results.resize(numSteps);
    results[0] = y;

    // Print initial state
    stream << "Time: " << t << " Value: " << y << "\n";

    // Manually compute the first few steps using FE or RK4
    for (int i = 1; i < steps_ && i < numSteps; ++i) {
        if (initMethod_ == "FE") {
            y += stepSize * f_rhs->value(y, t);  // Forward Euler formula
        } else if (initMethod_ == "RK4") {
            // Runge-Kutta 4 formula
            double k1 = stepSize * f_rhs->value(y, t);
            double k2 = stepSize * f_rhs->value(y + 0.5 * k1, t + 0.5 * stepSize);
            double k3 = stepSize * f_rhs->value(y + 0.5 * k2, t + 0.5 * stepSize);
            double k4 = stepSize * f_rhs->value(y + k3, t + stepSize);
            y += (k1 + 2*k2 + 2*k3 + k4) / 6;
        }
        t += stepSize;
        results[i] = y;
        // stream << "Time: " << t << " Value: " << y << "\n";
    }

    // Continue
    for (int currentStep = steps_; currentStep < numSteps; ++currentStep) {
        y = step(y, t);
        if (t + stepSize > finalTime) {
            t = finalTime;
        } else {
            t = initialTime + currentStep * stepSize; // Update time explicitly
        }
        results[currentStep] = y;
    }
}

// Setters
void ExplicitMultiStepSolver::setSteps(int steps) {
  if (steps <= 0){
    throw std::invalid_argument("'Steps' must be an positive integer.");
  }
    steps_ = steps;
    coeffs_.resize(steps);
}

void ExplicitMultiStepSolver::setInitMethod(const std::string &initMethod) {
    if (initMethod != "FE" && initMethod != "RK4") {
        throw std::invalid_argument("Initialization method must be 'FE' or 'RK4'.");
    }
    initMethod_ = initMethod;
}

// Getters
int ExplicitMultiStepSolver::getSteps() const {
    return steps_;
}

std::string ExplicitMultiStepSolver::getInitMethod() const {
    return initMethod_;
}

