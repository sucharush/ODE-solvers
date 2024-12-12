/**
 * @file SolverFactory.h
 * @brief Solver factory
 * @author csy
 * @date 05.12.24.
 */

#ifndef SOLVERFACTORY_H
#define SOLVERFACTORY_H

#include <memory>
#include <map>
#include <Eigen/Dense>
#include <string>
#include <iostream>
#include "AdamsBashforthSolver.h"
#include "BackwardEulerSolver.h"
#include "ForwardEulerSolver.h"
#include "RungeKuttaSolver.h"
#include "ModelProblemRHS.h"
#include "PolynomialRHS.h"

//! Structure for solver configuration
struct SolverConfig {
    std::string method;                      //!< Solver method (e.g., "RK", "AB")
    std::map<std::string, double> globalParams;  //!< Global parameters
    std::map<std::string, double> methodParams;  //!< Method-specific parameters
    // std::map<std::string, double> rhsParams;
    int order = 4;                           //!< Order for Runge-Kutta
    std::string initMethod = "RK4";          //!< Initial method for Adams-Bashforth
    int steps = 2;                           //!< Number of steps for Adams-Bashforth
    std::string type = "model";
    double decay = 0.3;
    Eigen::VectorXd coefficients;

    /// Method do validate the configuration
    void validate() const;
};

//!  Factory class to create solvers

class SolverFactory {
public:
    /// Method to create a (pointer to a) solver from a configuration
    /*!
    This method creates a solver from a given configuration
    @param config solver configuration
    */
    static std::unique_ptr<AbstractOdeSolver> createSolver(const SolverConfig& config);

private:
    /// Helper function to configure global parameters
    /*!
     This method configures a given solver with wanted parameters
    @param solver solver to configurated
    @param params map object that contains all base parameters and their values
    @see AbstractOdeSolver for the base parameters
    */
    static void configureGlobalParams(AbstractOdeSolver& solver, const std::map<std::string, double>& params);
};

#endif // SOLVERFACTORY_H
