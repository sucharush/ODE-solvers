//
// Created by ebaup on 07.12.24.
//

#ifndef KNOWNDERIVATIVERHS_H
#define KNOWNDERIVATIVERHS_H

#include "ODERightHandSide.h"

//!  Class for function with known derivative.
/*!
This is a class that represents function for which we know the derivative with respect to t.
*/

class KnownDerivativeRHS: public ODERightHandSide {
public:
    //! Constructor
    /*!
    This constructor sets the function and its derivative. By default, non-specified functions are set to null pointers.
    @param func (pointer on) function object for the right hand side
    @param deriv (pointer on) function object for the derivative of the right hand side
    */
    KnownDerivativeRHS(FuncType* func = nullptr, FuncType* deriv = nullptr);
    /// Destructor
    /*! This destructor deallocates the memory used by the derivative.
     * The memory used by the function is deallocated in the parent's destructor.
    */
    virtual ~KnownDerivativeRHS();
    /// Overriden implementation of the derivative evaluation.
    /*!
    This computes the exact value of the derivative at (y,t) with the given df.
    @param y space variable
    @param t time varianle
    @return (df/dt)(y,t)
    */
    virtual double derivative(double y, double t) const override;
protected:
    FuncType* df; //!< Pointer to the derivative (wrt t) of the right hand side function.
};

#endif //KNOWNDERIVATIVERHS_H
