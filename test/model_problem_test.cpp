//
// Created by ebaup on 30.11.24.
// Test file to test the solvers on the model problem.
//
#include <gtest/gtest.h>
#include <Eigen/Dense>
#include <iostream>

#include "ModelProblemRHS.h"
double const k_test = 2.0;
double const tol = 1e-6;

class ModelProblemTest : public::testing::Test {
protected:
    void SetUp() override {
        model = ModelProblemRHS(k_test);
    }
    // Shared resource for tests
    ModelProblemRHS model;
    /*
    double initialTime = 0.0;
    double finalTime = 10.0;
    double initialValue = 1.0;
    double stepSize = 0.1;
    */
};

// Test ModelProblemRHS
TEST_F(ModelProblemTest, RHSValueFunction) {
    double t = 0.0;
    for (int i = 0; i < 10; i++) {
        double y = i + i*0.1;
        double expected = -k_test*y;
        EXPECT_EQ(model.value(y, t), expected);
    }
}
TEST_F(ModelProblemTest, RHSValueDerivative) {
    double t = 0.0;
    for (int i = 0; i < 10; i++) {
        double y = i + i*0.1;
        double expected = -k_test;
        EXPECT_EQ(model.derivative(y, t), expected);
    }
}

/*
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
    for (int i = 0; i < solver.results.size(); i++) {
        double exp_val = std::exp(-k_test*y);
        EXPECT_NEAR(solver.results[i], exp_val, tol);
    }
}
*/

// Test Backward Euler solver on model problem