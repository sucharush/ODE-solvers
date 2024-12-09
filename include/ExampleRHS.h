//
// Created by csy on 2024/11/22.
//

#ifndef EXANMPLERHS_H
#define EXANMPLERHS_H

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

#endif //EXANMPLERHS_H