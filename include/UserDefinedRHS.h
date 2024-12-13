/**
 * @file UserDefinedRHS.h
 * @brief Some example functions for the right hand side of the ODE
 * @author csy
 * @date 22.11.24.
 */

#ifndef USERDEFINEDRHS_H
#define USERDEFINEDRHS_H

#include "UnknownDerivativeRHS.h"

//! Class for user-defined RHS

class UserDefinedRHS : public UnknownDerivativeRHS {
public:
    /// Constructor (with arbitrary return value)
    UserDefinedRHS() {
    f = std::make_shared<FuncType>([this](double y, double t) {
        return 0;
    });
    // The user can change manually the heritance to KnownDerivative and specify the explicit derivative df there:
    // // add the derivative if 'KnownDerivativeRHS'
    // df = std::make_shared<FuncType>([this](double y, double t) {
    //     return 0;
    // });
    }
    /// Simple destructor
    ~UserDefinedRHS() {}
};

#endif //USERDEFINEDRHS_H