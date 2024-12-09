//
// Created by csy on 2024/11/22.
//
#include "AbstractOdeSolver.h"
#include <iostream>
#include <iomanip> // For setting precision
#include <cmath>

void AbstractOdeSolver::SolveEquation(std::ostream& stream) {
    stream << std::fixed << std::setprecision(5);

    double t = initialTime;
    double y = initialValue;

    int numSteps = static_cast<int>((finalTime - initialTime) / stepSize) + 1;
    results.resize(numSteps);
    results[0] = y;

    // initial state
    // stream << "Time: " << t << "	Value: " << y << "\n";

    // Time-stepping loop
    for (int currentStep = 1; currentStep < numSteps; ++currentStep) {

        y = step(y, t);
        // double currentStepSize = stepSize;
        if (t + stepSize > finalTime) {
            t = finalTime;
        } else {
            t = initialTime + currentStep * stepSize; // Update time explicitly
        }
        // Compute the next step
        results[currentStep] = y;

        // Optional debug output
        // stream << "Time: " << t << "	Value: " << y << "\n";
    }
}

void AbstractOdeSolver::PrintResults(std::ostream& stream) const {
    stream << "Time, Value\n";
    double t = initialTime;
    for (int i = 0; i < results.size(); ++i) {
        stream << std::fixed << std::setprecision(5) << t << ", " << results[i] << "\n";
        t += stepSize;  // Increment time by step size
    }
}

