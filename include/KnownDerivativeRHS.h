//
// Created by ebaup on 07.12.24.
//

#ifndef KNOWNDERIVATIVERHS_H
#define KNOWNDERIVATIVERHS_H

#include "ODERightHandSide.h"

class KnownDerivativeRHS: public ODERightHandSide {
public:
    // Constructor
    //KnownDerivativeRHS(): df(nullptr) {}
    KnownDerivativeRHS(FuncType* func = nullptr, FuncType* deriv = nullptr);
    virtual ~KnownDerivativeRHS();
    virtual double derivative(double y, double t) const override;
protected:
    FuncType* df;
};

#endif //KNOWNDERIVATIVERHS_H
