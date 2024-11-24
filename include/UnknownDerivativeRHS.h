//
// Created by csy on 2024/11/22.
//
#include "ODERightHandSide.h"

#include <functional>
#include <cmath>

// typedef for function and derivative type
typedef std::function<double(double, double)> FuncType;
typedef std::function<double(double, double)> DerivativeType;

class UnknownDerivativeRHS : public ODERightHandSide {
public:
    UnknownDerivativeRHS(FuncType func, double h = 1e-8);
    virtual ~UnknownDerivativeRHS() {}

    double value(double y, double t) const override {
        return fun(y, t);
    }
    double derivative(double y, double t) const override;

private:
    FuncType fun;
    double stepForDfun;
};
