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
/// Generate random distribution for tests
std::random_device rd_poly;
std::mt19937 gen_poly(rd_poly()); //!< use specific engine for generation

std::uniform_real_distribution<> dis_poly(-100.0, 10.0);

int order_poly1 = 5;
Eigen::VectorXd coeffs1 = Eigen::VectorXd::Zero(order_poly1 + 1);
// Set up the weights randomly
for (int i = 0; i < order_poly1; ++i) {
    coeffs1(i) = dis_poly(gen_poly);
}


double computeAnalyticalSolution(double t, double y0, double k) {
    return y0 * std::exp(-k * t);
}

class ModelProblemTest : public::testing::Test {
protected:
    std::unique_ptr<ODERightHandSide> model = std::make_unique<ModelProblemRHS>(k_test);

    double initialTime = 0.0;
    double finalTime = 1.0;
    double initialValue = 1.0;
    double stepSize = 0.1;

};

// Test ModelProblemRHS
TEST_F(ModelProblemTest, RHSValueFunction) {
    for (int i = 0; i < 10; i++) {
        double t = 0.5;
        double y = i + i*0.1;
        double expected = -k_test*y;
        EXPECT_EQ(model->value(y, t), expected);
    }
}
TEST_F(ModelProblemTest, RHSValueDerivative) {
    double t = 0.5;
    for (int i = 0; i < 10; i++) {
        double y = i + i*0.1;
        double expected = 0.0;
        EXPECT_EQ(model->derivative(y, t), expected);
    }
}


// Test Forward Euler solver on model problem
#include "ForwardEulerSolver.h"

TEST_F(ModelProblemTest, FE) {
    ForwardEulerSolver solver;
    solver.SetStepSize(stepSize);
    solver.SetTimeInterval(initialTime, finalTime);
    solver.SetInitialValue(initialValue);
    solver.SetRightHandSide(std::move(model));
    solver.SolveEquation(std::cout);
    int numSteps = solver.results.size();

    double t = initialTime;
    for (int i = 0; i < numSteps; ++i, t += stepSize) {
        double exp_val = computeAnalyticalSolution(t, initialValue, k_test);
        EXPECT_NEAR(solver.results[i], exp_val, TOL_SOLUTION);
    }
}


// Test Backward Euler solver on model problem
#include "BackwardEulerSolver.h"

TEST_F(ModelProblemTest, BE) {
    BackwardEulerSolver solver;
    solver.SetStepSize(stepSize);
    solver.SetTimeInterval(initialTime, finalTime);
    solver.SetInitialValue(initialValue);
    solver.SetRightHandSide(std::move(model));
    solver.SolveEquation(std::cout);
    int numSteps = solver.results.size();

    double t = initialTime;
    for (int i = 0; i < numSteps; ++i, t += stepSize) {
        double exp_val = computeAnalyticalSolution(t, initialValue, k_test);
        EXPECT_NEAR(solver.results[i], exp_val, TOL_SOLUTION);
    }
}

#include "RungeKuttaSolver.h"
TEST_F(ModelProblemTest, RK) {
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
            double exp_val = computeAnalyticalSolution(t, initialValue, k_test);
            EXPECT_NEAR(solver.results[i], exp_val, TOL_SOLUTION);
        }
    }

}

#include "AdamsBashforthSolver.h"

TEST_F(ModelProblemTest, AB) {
    AdamsBashforthSolver solver(4, "FE");
    solver.SetStepSize(stepSize);
    solver.SetTimeInterval(initialTime, finalTime);
    solver.SetInitialValue(initialValue);
    solver.SetRightHandSide(std::move(model));
    solver.SolveEquation(std::cout);
    int numSteps = solver.results.size();

    double t = initialTime;
    for (int i = 0; i < numSteps; ++i, t += stepSize) {
        double exp_val = computeAnalyticalSolution(t, initialValue, k_test);
        EXPECT_NEAR(solver.results[i], exp_val, TOL_SOLUTION);
    }
}
