//
// Created by ebaup on 10.12.24.
// Test file for Function class

#include <gtest/gtest.h>
#include <random>
#include "utils.h"
#include "ODERightHandSide.h"
#include "KnownDerivativeRHS.h"
#include "UnknownDerivativeRHS.h"

/// Generate random distribution for tests
std::random_device rd;
std::mt19937 gen(rd()); //!< use specific engine for generation

double const max_d = 50.0; //!< Maximum absolute value for the distribution
/// Sets up distribution in [-50, 50]
std::uniform_real_distribution<> dis(-max_d, max_d);
/// Randomly generated numbers
double a = dis(gen), b = dis(gen), c = dis(gen), d = dis(gen);

double f1(double y, double t) {return a*y + b + c*t + d*t*y; }
double df1(double y, double t) { return c + d*y; }

double f2(double y, double t) {return t*t + std::exp(t)*y; }
double df2(double y, double t) {return 2*t + std::exp(t)*y; }

// Test suite for linear function (f1)
class FunctionTestLinear : public::testing::Test {
protected:
    std::shared_ptr<FuncType> func1;
    std::shared_ptr<FuncType> dfunc1;
    void SetUp() override {
        func1 = std::make_shared<FuncType>(f1);
        dfunc1 = std::make_shared<FuncType>(df1);
    }
    void TearDown() override {
        // smart pointers are automatically deleted
    }
};

// Test suite for f2
class ExpAndSquareFunctionTest : public::testing::Test {
protected:
    std::shared_ptr<FuncType> func2;
    std::shared_ptr<FuncType> dfunc2;

    void SetUp() override {
        func2 = std::make_shared<FuncType>(f2);
        dfunc2 = std::make_shared<FuncType>(df2);
    }
};

// KnownDerivative (KD) Tests
TEST_F(FunctionTestLinear, KD){
    ODERightHandSide* rhs;
    rhs = new KnownDerivativeRHS(func1, dfunc1);
    for (int i = 0; i < 10; ++i) {
        double y = 0.5*i; double t = 0.1*i;
        EXPECT_NEAR(rhs->value(y, t), f1(y, t), TOL_EQ);
        EXPECT_NEAR(rhs->derivative(y, t), df1(y, t), TOL_EQ);
    }
    delete rhs;
}

TEST_F(ExpAndSquareFunctionTest, KD){
    ODERightHandSide* rhs;
    rhs = new KnownDerivativeRHS(func2, dfunc2);
    for (int i = 0; i < 10; ++i) {
        double y = 0.5*i; double t = 0.1*i;
        EXPECT_NEAR(rhs->value(y, t), f2(y, t), TOL_EQ);
        EXPECT_NEAR(rhs->derivative(y, t), df2(y, t), TOL_EQ);
    }
    delete rhs;
}

// UnknownDerivative (UD) Tests
TEST_F(FunctionTestLinear, UD){
    ODERightHandSide* rhs;
    rhs = new UnknownDerivativeRHS(func1, 1e-4);
    for (int i = 0; i < 10; ++i) {
        double y = 0.5*i; double t = 0.1*i;
        EXPECT_NEAR(rhs->value(y, t), f1(y, t), TOL_EQ);
        EXPECT_NEAR(rhs->derivative(y, t), df1(y, t), TOL_EQ);
    }
    delete rhs;
}

TEST_F(ExpAndSquareFunctionTest, UD){
    ODERightHandSide* rhs;
    rhs = new UnknownDerivativeRHS(func2); // use default parameters for h
    for (int i = 0; i < 10; ++i) {
        double y = 0.5*i; double t = 0.1*i;
        EXPECT_NEAR(rhs->value(y, t), f2(y, t), TOL_EQ);
        EXPECT_NEAR(rhs->derivative(y, t), df2(y, t), TOL_EQ);
    }
    delete rhs;
}