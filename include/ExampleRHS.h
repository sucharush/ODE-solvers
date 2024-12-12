/**
 * @file ExampleRHS.h
 * @brief Some example functions for the right hand side of the ODE
 * @author csy
 * @date 22.11.24.
 */

#ifndef EXAMPLERHS_H
#define EXAMPLERHS_H

#include "KnownDerivativeRHS.h"

// for model problem y'(t) = -ky(t)
// analytical solution: y = exp(-kt)

class ExampleRHS : public KnownDerivativeRHS {
public:
    // Constructor (default and with parameter k)
    ExampleRHS(): k_(0.0) {}
    ExampleRHS(double k);
    ~ExampleRHS() {}

private:
    double k_;
};

#endif //EXAMPLERHS_H