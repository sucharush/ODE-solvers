/**
 * @file UserDefinedRHS.h
 * @brief Some example functions for the right hand side of the ODE
 * @author csy
 * @date 22.11.24.
 */

#ifndef USERDEFINEDRHS_H
#define USERDEFINEDRHS_H

#include "UnknownDerivativeRHS.h"

// for model problem y'(t) = -ky(t)
// analytical solution: y = exp(-kt)

class UserDefinedRHS : public UnknownDerivativeRHS {
public:
    // Constructor (default and with parameter k)
    UserDefinedRHS();
    ~UserDefinedRHS() {}
};

#endif //USERDEFINEDRHS_H