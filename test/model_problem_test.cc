//
// Created by ebaup on 30.11.24.
// Test file to test the solvers on the model problem.
//
#include <gtest/gtest.h>
#include <iostream>
#include <memory>
#include <random>
#include "ModelProblemRHS.h"
#include "ODERightHandSide.h"
#include "utils.h"

/// Generate random distribution for tests
std::random_device rd_k;
std::mt19937 gen_k(rd_k()); //!< use specific engine for generation

std::uniform_real_distribution<> dis_k(0.0, 1.0);
double const k_test = dis_k(gen_k);

/// Analytical solution for the test on the model problem
double AnalyticalSolutionModel(double t, double y0, double k) {
    return y0 * std::exp(-k * t); // define analytical solution if you know
}

class ModelProblemTest : public::testing::Test {
protected:
    std::unique_ptr<ODERightHandSide> model = std::make_unique<ModelProblemRHS>(k_test);

    double initialTime = 0.0;
    double finalTime = 1.0;
    double initialValue = 1.0;
    double stepSize = 0.01;

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
        double exp_val = AnalyticalSolutionModel(t, initialValue, k_test);
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
        double exp_val = AnalyticalSolutionModel(t, initialValue, k_test);
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
        solver.SetOrder(order);
        double t = initialTime;
        for (int i = 0; i < numSteps; ++i, t += stepSize) {
            double exp_val = AnalyticalSolutionModel(t, initialValue, k_test);
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
        double exp_val = AnalyticalSolutionModel(t, initialValue, k_test);
        EXPECT_NEAR(solver.results[i], exp_val, TOL_SOLUTION);
    }
}
