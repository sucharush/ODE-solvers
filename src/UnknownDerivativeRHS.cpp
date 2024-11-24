//
// Created by ebaup on 24.11.24.
//

#include "UnknownDerivativeRHS.h"

UnknownDerivativeRHS::UnknownDerivativeRHS(FuncType func, double h)  : fun(func), stepForDfun(h) {};

double UnknownDerivativeRHS::derivative(double y, double t) const{
  return (fun(y + stepForDfun, t) - fun(y - stepForDfun, t)) / (2 * stepForDfun);
}