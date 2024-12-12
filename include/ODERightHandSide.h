/**
 * @file ODERightHandSide.h
 * @brief Base function class.
 * @author csy
 * @date 22.11.24.
 */

#ifndef ODERIGHTHANDSIDE_H
#define ODERIGHTHANDSIDE_H

#include "utils.h"
#include <iostream>

//!  (Abstract) base function class.
/*!
This is the base function class, that allows us to represent a function (together with its derivative).
@note We kept the name ODERightHandSide, but it could have been renamed simply to Function.
*/

class ODERightHandSide {
public:
    //! Constructor of a function instance
    /*!
    This constructor sets the function object of the right hand side of the ODE.
    @param fun Pointer to a FuncType, by default: null pointer.
    @see FuncType in utils.h
    */
    ODERightHandSide(FuncType* fun = nullptr): f(fun) {}
    //! Destructor
    /*!
    This destructor deallocates the memory used by the right hand side.
    */
    virtual ~ODERightHandSide() {
        delete f;
    }

    /// Computes the value at the function.
    /*!
    @param y space variable
    @param t time varianle
    @return f(y,t)
    */
    virtual double value(double y, double t) const;

    /// Computes the value of the derivative with respect to t.
    /*!
    Depending on the function, it will either call the real derivative, or approximate it.
    @param y space variable
    @param t time varianle
    @return (df/dt)(y,t) or an approximation
    */
    virtual double derivative(double y, double t) const = 0;
protected:
    FuncType* f; //!< Pointer to the right hand side function.
};

#endif //ODERIGHTHANDSIDE_H
