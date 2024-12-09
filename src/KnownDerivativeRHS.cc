//
// Created by ebaup on 07.12.24.
//

#include "KnownDerivativeRHS.h"

KnownDerivativeRHS::KnownDerivativeRHS(FuncType* fun, FuncType* deriv) : ODERightHandSide(fun), df(deriv) {}

KnownDerivativeRHS::~KnownDerivativeRHS() {
    delete df;
}

double KnownDerivativeRHS::derivative(double y, double t) const{
    return (*df)(y, t);
}