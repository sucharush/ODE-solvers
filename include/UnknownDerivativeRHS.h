//
// Created by csy on 2024/11/22.
//
#include "ODERightHandSide.h"

#include "utils.h"


class UnknownDerivativeRHS : public ODERightHandSide {
public:
    UnknownDerivativeRHS(FuncType* fun = nullptr, double h = 1e-8);
    virtual ~UnknownDerivativeRHS() { delete f;}

    virtual double derivative(double y, double t) const override;

private:
    // member that defines the precision for the approximation of df
    double stepForDf;
};
