//
// Created by ebaup on 07.12.24.
//

#include "KnownDerivativeRHS.h"

KnownDerivativeRHS::KnownDerivativeRHS(std::shared_ptr<FuncType> func, std::shared_ptr<FuncType> deriv) : ODERightHandSide(func), df(deriv) {}

double KnownDerivativeRHS::derivative(double y, double t) const{
    return (*df)(y, t);
}