/**
 * @file ModelProblemRHS.h
 * @brief Right-hand side function for the model problem
 * @author csy
 * @date 22.11.24.
 */
#ifndef MODELPROBLEMRHS_H
#define MODELPROBLEMRHS_H
#include "KnownDerivativeRHS.h"

//! Class for the RHS of the model problem
/*!
The model problem is the ODE y'(t) = -ky(t)
Its analytical solution is y = exp(-kt)
*/

class ModelProblemRHS : public KnownDerivativeRHS {
public:
    /// Default constructor (gives a zero function)
    ModelProblemRHS(): k_(0.0) {}
    /// Constructor with specified parameter
    /*!
    The constructor creates the function -k*y that defines a model problem.
    @param k determines the right-hand side.
    */
    ModelProblemRHS(double k);
    /// Simple destructor
    ~ModelProblemRHS() {}

protected:
    double k_; //!< variable that defines the model problem and its RHS
};
#endif //MODELPROBLEMRHS_H
