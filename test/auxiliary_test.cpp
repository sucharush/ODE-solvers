//
// Created by ebaup on 10.12.24.
// Test file for Function class

#include <gtest/gtest.h>
#include <random>
#include "utils.h"
#include "ODERightHandSide.h"
#include "KnownDerivativeRHS.h"
#include "UnknownDerivativeRHS.h"

double const a = 2.0;
double const b = -3.0;
double const c = 5.0;
double const d = -1.5;

double f1(double y, double t) {return a*y + b + c*t; }
double df1(double y, double t) { return c; }

double f2(double y, double t) {return y*t; }
double df2(double y, double t) {return y; }

double f3(double y, double t) {return t*t + std::exp(t)*y; }
double df3(double y, double t) {return 2*t + std::exp(t)*y; }

class FunctionTest : public::testing::Test {
protected:
    FuncType* func1;
    FuncType* dfunc1;
    FuncType* func2;
    FuncType* dfunc2;
    FuncType* func3;
    FuncType* dfunc3;
    ODERightHandSide* knownRHS1;
    ODERightHandSide* unknownRHS1;
    ODERightHandSide* knownRHS2;
    ODERightHandSide* unknownRHS2;
    ODERightHandSide* knownRHS3;
    ODERightHandSide* unknownRHS3;

    void SetUp() override {
        FuncType* func1 = new FuncType(f1);
        FuncType* dfunc1 = new FuncType(df1);
        FuncType* func2 = new FuncType(f2);
        FuncType* dfunc2 = new FuncType(df2);
        FuncType* func3 = new FuncType(f3);
        FuncType* dfunc3 = new FuncType(df3);
        knownRHS1 = new KnownDerivativeRHS(func1, dfunc1);
        unknownRHS1 = new UnknownDerivativeRHS(func1, 1e-6);
        knownRHS2 = new KnownDerivativeRHS(func2, dfunc2);
        unknownRHS2 = new UnknownDerivativeRHS(func2, 1e-6);
        knownRHS3 = new KnownDerivativeRHS(func3, dfunc3);
        unknownRHS3 = new UnknownDerivativeRHS(func3, 1e-6);
    }
    void TearDown() override {
        delete knownRHS1;
        delete knownRHS2;
        delete knownRHS3;
        // other pointers are automatically deleted
    }

};

// KnownDerivative (KD) Tests
TEST_F(FunctionTest, KD_linear){
    for (int i = 0; i < 10; ++i) {
        double y = 0.5*i; double t = 0.1*i;
        EXPECT_NEAR(knownRHS1->value(y, t), f1(y, t), TOL_EQ);
        EXPECT_NEAR(knownRHS1->derivative(y, t), df1(y, t), TOL_EQ);
    }
}

TEST_F(FunctionTest, KD_dep){
    for (int i = 0; i < 10; ++i) {
        double y = 0.5*i; double t = 0.1*i;
        EXPECT_NEAR(knownRHS2->value(y, t), f2(y, t), TOL_EQ);
        EXPECT_NEAR(knownRHS2->derivative(y, t), df2(y, t), TOL_EQ);
    }
}

TEST_F(FunctionTest, KD_dep2){
    for (int i = 0; i < 10; ++i) {
        double y = 0.5*i; double t = 0.1*i;
        EXPECT_NEAR(knownRHS3->value(y, t), f3(y, t), TOL_EQ);
        EXPECT_NEAR(knownRHS3->derivative(y, t), df3(y, t), TOL_EQ);
    }
}

// UnknownDerivative (UD) Tests
TEST_F(FunctionTest, UD_linear){
    for (int i = 0; i < 10; ++i) {
        double y = 0.5*i; double t = 0.1*i;
        EXPECT_NEAR(unknownRHS1->value(y, t), f1(y, t), TOL_EQ);
        EXPECT_NEAR(unknownRHS1->derivative(y, t), df1(y, t), TOL_EQ);
    }
}

TEST_F(FunctionTest, UD_dep){
    for (int i = 0; i < 10; ++i) {
        double y = 0.5*i; double t = 0.1*i;
        EXPECT_NEAR(unknownRHS2->value(y, t), f2(y, t), TOL_EQ);
        EXPECT_NEAR(unknownRHS2->derivative(y, t), df2(y, t), TOL_EQ);
    }
}

TEST_F(FunctionTest, UD_dep2){
    for (int i = 0; i < 10; ++i) {
        double y = 0.5*i; double t = 0.1*i;
        EXPECT_NEAR(unknownRHS3->value(y, t), f3(y, t), TOL_EQ);
        EXPECT_NEAR(unknownRHS3->derivative(y, t), df3(y, t), TOL_EQ);
    }
}
