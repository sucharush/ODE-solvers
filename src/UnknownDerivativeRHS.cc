//
// Created by ebaup on 24.11.24.
//

#include "UnknownDerivativeRHS.h"

UnknownDerivativeRHS::UnknownDerivativeRHS(FuncType* func, double h)  : ODERightHandSide(func), stepForDf(h) {}

double UnknownDerivativeRHS::derivative(double y, double t) const{
  // we compute the approximate derivative with centered difference
  return ((*f)(y , t+ stepForDf) - (*f)(y , t- stepForDf)) / (2 * stepForDf);
}