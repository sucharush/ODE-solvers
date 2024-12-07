//
// Created by ebaup on 30.11.24.
// Test file to test the solvers on the model problem.
//
#include <gtest/gtest.h>
#include <Eigen/Dense>
#include <iostream>
#include <memory>
#include "ModelProblemRHS.h"
#include "ODERightHandSide.h"
#include "utils.h"

double const k_test = 0.3;
double computeAnalyticalSolution(double t, double y0, double k) {
    return y0 * std::exp(-k * t);
}

class ModelProblemTest : public::testing::Test {
protected:
    /*
    void SetUp() override {
        model = new ModelProblemRHS(k_test);
    }
    void TearDown() override {
        delete model;
    }
    */
    // Shared resource for tests
    std::unique_ptr<ODERightHandSide> model = std::make_unique<ModelProblemRHS>(k_test);

    double initialTime = 0.0;
    double finalTime = 10.0;
    double initialValue = 1.0;
    double stepSize = 0.1;

};

// Test ModelProblemRHS
TEST_F(ModelProblemTest, RHSValueFunction) {
    double t = 1.0;
    for (int i = 0; i < 10; i++) {
        double y = i + i*0.1;
        double expected = -k_test*y;
        EXPECT_EQ(model->value(y, t), expected);
    }
}
TEST_F(ModelProblemTest, RHSValueDerivative) {
    double t = 1.0;
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
    double y = 1.0;
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
    double y = 1.0;
    int numSteps = solver.results.size();

    double t = initialTime;
    for (int i = 0; i < numSteps; ++i, t += stepSize) {
        double exp_val = computeAnalyticalSolution(t, initialValue, k_test);
        EXPECT_NEAR(solver.results[i], exp_val, TOL_SOLUTION);
    }
}