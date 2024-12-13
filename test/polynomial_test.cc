//
// Created by ebaup on 12.12.24.
// Test file to test the solvers on the polynomial.
//
#include <gtest/gtest.h>
#include <Eigen/Dense>
#include <iostream>
#include <memory>
#include "PolynomialRHS.h"
#include "ODERightHandSide.h"
#include "utils.h"

Eigen::VectorXd coeffs = Eigen::VectorXd::Map((double[]){1, 2}, 2);

double computeAnalyticalSolution(double t, double y0) {
    double C = y0 + 0.5;  // Calculate the integration constant C
    return C * exp(2 * t) - 0.5;  // y = Ce^(2t) - 0.5
}

class PolyRHSTest : public::testing::Test {
protected:
    std::unique_ptr<ODERightHandSide> model = std::make_unique<PolynomialRHS>(coeffs);

    double initialTime = 0.0;
    double finalTime = 1.0;
    double initialValue = 1.0;
    double stepSize = 0.001;
};


// Test Forward Euler solver on model problem
#include "ForwardEulerSolver.h"
double stepsize_euler = 1e-5; // FE and BE need smaller step size

TEST_F(PolyRHSTest, FE) {
    ForwardEulerSolver solver;
    solver.SetStepSize(stepsize_euler);
    solver.SetTimeInterval(initialTime, finalTime);
    solver.SetInitialValue(initialValue);
    solver.SetRightHandSide(std::move(model));
    solver.SolveEquation(std::cout);
    int numSteps = solver.results.size();

    double t = initialTime;
    for (int i = 0; i < numSteps; ++i, t += stepsize_euler) {
        double exp_val = computeAnalyticalSolution(t, initialValue);
        EXPECT_NEAR(solver.results[i], exp_val, TOL_SOLUTION);
    }
}


// Test Backward Euler solver on model problem
#include "BackwardEulerSolver.h"

TEST_F(PolyRHSTest, BE) {
    BackwardEulerSolver solver;
    solver.SetStepSize(stepsize_euler);
    solver.SetTimeInterval(initialTime, finalTime);
    solver.SetInitialValue(initialValue);
    solver.SetRightHandSide(std::move(model));
    solver.SolveEquation(std::cout);
    int numSteps = solver.results.size();

    double t = initialTime;
    for (int i = 0; i < numSteps; ++i, t += stepsize_euler) {
        double exp_val = computeAnalyticalSolution(t, initialValue);
        EXPECT_NEAR(solver.results[i], exp_val, TOL_SOLUTION);
    }
}

#include "RungeKuttaSolver.h"
TEST_F(PolyRHSTest, RK) {
    RungeKuttaSolver solver(2);
    solver.SetStepSize(stepSize);
    solver.SetTimeInterval(initialTime, finalTime);
    solver.SetInitialValue(initialValue);
    solver.SetRightHandSide(std::move(model));
    solver.SolveEquation(std::cout);
    int numSteps = solver.results.size();
    // Loop over the defined orders (2,3,4)
    for (int order = 2; order <=4; ++order) {
        solver.SetType(order);
        double t = initialTime;
        for (int i = 0; i < numSteps; ++i, t += stepSize) {
            double exp_val = computeAnalyticalSolution(t, initialValue);
            EXPECT_NEAR(solver.results[i], exp_val, TOL_SOLUTION);
        }
    }

}

#include "AdamsBashforthSolver.h"

TEST_F(PolyRHSTest, AB) {
    AdamsBashforthSolver solver(3, "RK4");
    solver.SetStepSize(stepSize);
    solver.SetTimeInterval(initialTime, finalTime);
    solver.SetInitialValue(initialValue);
    solver.SetRightHandSide(std::move(model));
    solver.SolveEquation(std::cout);
    int numSteps = solver.results.size();

    double t = initialTime;
    for (int i = 0; i < numSteps; ++i, t += stepSize) {
        double exp_val = computeAnalyticalSolution(t, initialValue);
        EXPECT_NEAR(solver.results[i], exp_val, TOL_SOLUTION);
    }
}
