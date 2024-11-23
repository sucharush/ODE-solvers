//
// Created by csy on 2024/11/22.
//

#ifndef ODERIGHTHANDSIDE_H
#define ODERIGHTHANDSIDE_H
class ODERightHandSide {
public:
    virtual ~ODERightHandSide() {}

    // the function at (y, t)
    virtual double value(double y, double t) const = 0;

    // derivative with respect to y at time t
    virtual double derivative(double y, double t) const = 0;
};

#endif //ODERIGHTHANDSIDE_H
