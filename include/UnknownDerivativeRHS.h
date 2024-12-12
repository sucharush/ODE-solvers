//
// Created by csy on 2024/11/22.
//

#ifndef UNKNOWNDERIVATIVERHS_H
#define UNKNOWNDERIVATIVERHS_H

#include "ODERightHandSide.h"
#include "utils.h"

//!  Class for function with unknown derivative.
/*!
This is a class that represents function for which we don't know the derivative with respect to t.
The derivative is approximated with a centered difference scheme.
*/

class UnknownDerivativeRHS : public ODERightHandSide {
public:
    //! Constructor
    /*!
    This constructor sets the function and its derivative and the step size for the approximation scheme.
    @param func (pointer on) function object for the right hand side, default: null pointer
    @param h step size for the approximation scheme
    */
    UnknownDerivativeRHS(FuncType* func = nullptr, double h = 1e-8);
    /// Destructor (the memory for f is deallocated in the parent's destructor)
    virtual ~UnknownDerivativeRHS() {}
    /// Overriden implementation of the derivative evaluation.
    /*!
    This computes an approximation of the derivative, using a centered difference scheme.
    @param y space variable
    @param t time varianle
    @return an approximation of (df/dt)(y,t)
    */
    virtual double derivative(double y, double t) const override;

private:
    double stepForDf; //!< Step size for the precision of the approximation scheme
};

#endif