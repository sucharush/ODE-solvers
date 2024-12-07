//
// Created by csy on 2024/11/22.
//

#ifndef ODERIGHTHANDSIDE_H
#define ODERIGHTHANDSIDE_H

#include "utils.h"
#include <iostream>

class ODERightHandSide {
public:
    ODERightHandSide(): f(nullptr) {}
    ODERightHandSide(FuncType* fun): f(fun) {}
    virtual ~ODERightHandSide() {
        delete f;
    }

    // the function at (y, t)
    virtual double value(double y, double t) const;

    // derivative with respect to y at time t
    virtual double derivative(double y, double t) const = 0;
protected:
    FuncType* f;
};

#endif //ODERIGHTHANDSIDE_H
