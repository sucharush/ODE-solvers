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
    // Constructor
    //KnownDerivativeRHS(): df(nullptr) {}
    //! Constructor
    /*!
    This constructor sets the function and its derivative. By default, non-specified functions are set to null pointers.
    @param func (pointer on) function object for the right hand side
    @param deriv (pointer on) function object for the derivative of the right hand side
    */
    KnownDerivativeRHS(FuncType* func = nullptr, FuncType* deriv = nullptr);
    /// Destructor
    virtual ~KnownDerivativeRHS();
    virtual double derivative(double y, double t) const override;
protected:
    FuncType* df;
};

#endif //KNOWNDERIVATIVERHS_H
