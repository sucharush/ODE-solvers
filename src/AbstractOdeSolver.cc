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
    double e = 0;

    int numSteps = static_cast<int>((finalTime - initialTime) / stepSize) + 1;
    results.resize(numSteps);
    results[0] = y;

    // initial state
    stream << "Time: " << t << "	Value: " << y << "\n";

    // Time-stepping loop
    for (int i= 1; i < numSteps; ++i) {
        double currentStepSize = stepSize;
        if (t + stepSize > finalTime) {
            currentStepSize = finalTime - t;
        }

        // Compute the next step
        y = step(y, t);
        results[i] = y;
        // e = std::exp(-0.3*t); // just to compare with the exact solution
        // stream << "Time: " << t << "	Numerical: " << y <<"	Exact: " << e << "\n";
        t += currentStepSize;
        results[i] = y;
        //updated state
        // stream << "Time: " << t << "	Numerical: " << y << "\n";
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

