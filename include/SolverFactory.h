#ifndef SOLVERFACTORY_H
#define SOLVERFACTORY_H

#include <memory>
#include <map>
#include <string>
#include <iostream>
#include "AdamsBashforthSolver.h"
#include "BackwardEulerSolver.h"
#include "ForwardEulerSolver.h"
#include "RungeKuttaSolver.h"

// Struct for solver configuration
struct SolverConfig {
    std::string method;                      // Solver method (e.g., "RK", "AB")
    std::map<std::string, double> globalParams;  // Global parameters
    std::map<std::string, double> methodParams;  // Method-specific parameters
    int order = 4;                           // Defaulted order for Runge-Kutta
    std::string initMethod = "RK4";          // Defaulted init method for AB
    int steps = 2;                           // Default steps for AB

    // Validate the configuration
    void validate() const;
};

// Factory class to create solvers
class SolverFactory {
public:
    static std::unique_ptr<AbstractOdeSolver> createSolver(const SolverConfig& config);

private:
    // Helper function to configure global parameters
    static void configureGlobalParams(AbstractOdeSolver& solver, const std::map<std::string, double>& params);
};

#endif // SOLVERFACTORY_H
