//
// Created by csy on 2024/12/12.
//

#ifndef MODELPROBLEMRHS_H
#define MODELPROBLEMRHS_H
#include "KnownDerivativeRHS.h"

// for model problem y'(t) = -ky(t)
// analytical solution: y = exp(-kt)

class ModelProblemRHS : public KnownDerivativeRHS {
public:
    // Constructor (default and with parameter k)
    ModelProblemRHS(): k_(0.0) {}
    ModelProblemRHS(double k);
    ~ModelProblemRHS() {}

protected:
    double k_;
};
#endif //MODELPROBLEMRHS_H
