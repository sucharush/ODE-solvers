//
// Created by csy on 2024/11/22.
//

#ifndef MODELPROBLEMSRHS_H
#define MODELPROBLEMSRHS_H

#include "KnownDerivativeRHS.h"

// for model problem y'(t) = -ky(t)
// analytical solution: y = exp(-kt)

class ModelProblemRHS : public KnownDerivativeRHS {
public:
    // Constructor (default and with parameter k)
    ModelProblemRHS(double k = 0.0);
    ~ModelProblemRHS() {}

private:
    double k_;
};

#endif //MODELPROBLEMSRHS_H