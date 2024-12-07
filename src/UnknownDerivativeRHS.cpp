//
// Created by ebaup on 24.11.24.
//

#include "UnknownDerivativeRHS.h"

UnknownDerivativeRHS::UnknownDerivativeRHS(FuncType* fun, double h)  : ODERightHandSide(fun), stepForDf(h) {}

double UnknownDerivativeRHS::derivative(double y, double t) const{
  // we compute the approximate derivative with centered difference
  return ((*f)(y + stepForDf, t) - (*f)(y - stepForDf, t)) / (2 * stepForDf);
}