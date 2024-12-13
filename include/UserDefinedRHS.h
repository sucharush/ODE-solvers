/**
 * @file UserDefinedRHS.h
 * @brief Some example functions for the right hand side of the ODE
 * @author csy
 * @date 22.11.24.
 */

#ifndef USERDEFINEDRHS_H
#define USERDEFINEDRHS_H

#include "UnknownDerivativeRHS.h"

class UserDefinedRHS : public UnknownDerivativeRHS {
public:
    // Constructor (with arbitrary return value)
    UserDefinedRHS() {
    f = std::make_shared<FuncType>([this](double y, double t) {
        return 0;
    });
    // // add the derivative if 'KnownDerivativeRHS'
    // df = std::make_shared<FuncType>([this](double y, double t) {
    //     return 0;
    // });
    }
    ~UserDefinedRHS() {}
};

#endif //USERDEFINEDRHS_H