//
// Created by csy on 2024/11/22.
//

#ifndef ODERIGHTHANDSIDE_H
#define ODERIGHTHANDSIDE_H

#include "utils.h"
#include <iostream>

class ODERightHandSide {
public:
    // Constructor (with parameter and default)
    ODERightHandSide(FuncType* fun = nullptr): f(fun) {}
    virtual ~ODERightHandSide() {
        delete f;
    }

    // the function at (y, t)
    virtual double value(double y, double t) const;

    // derivative with respect to t
    virtual double derivative(double y, double t) const = 0;
protected:
    FuncType* f;
};

#endif //ODERIGHTHANDSIDE_H
