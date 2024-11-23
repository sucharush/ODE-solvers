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

    // initial state
    stream << "Time: " << t << "	Value: " << y << "\n";

    // Time-stepping loop
    while (t < finalTime) {

        double currentStepSize = stepSize;
        if (t + stepSize > finalTime) {
            currentStepSize = finalTime - t;
        }

        // Compute the next step
        y = step(y, t);
        // e = std::exp(-0.3*t); // just to compare with the exact solution
        // stream << "Time: " << t << "	Numerical: " << y <<"	Exact: " << e << "\n";
        t += currentStepSize;

        //updated state
        stream << "Time: " << t << "	Numerical: " << y << "\n";
    }
}