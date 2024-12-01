//
// Created by csy on 2024/11/22.
//
#include "ODERightHandSide.h"

// for model problem y'(t) = -ky(t)
// analytical solution: y = exp(-kt)

class ModelProblemRHS : public ODERightHandSide {
public:
    ModelProblemRHS(double k) : k_(k) {}
    ModelProblemRHS() : k_(0.0) {}
    virtual ~ModelProblemRHS() {}

    double value(double y, double t) const override {
        return -k_ * y;
    }
    double derivative(double y, double t) const override {
        return -k_;
    }

private:
    double k_;
};
