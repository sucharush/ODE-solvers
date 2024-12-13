/**
 * @file PolynomialRHS.h
 * @brief Polynomial right-hand side function
 * @author csy
 * @date 12.12.24.
 */
#ifndef POLYNOMIALRHS_H
#define POLYNOMIALRHS_H
#include "KnownDerivativeRHS.h"
#include <Eigen/Dense>

//! Class for polynomial functions

class PolynomialRHS : public KnownDerivativeRHS {
  public:
    /// Constructor
    /*!
     This constructor creates a polynomial function from its coefficients.
     @param coeffs coefficients defining the polynomial
    */
    explicit PolynomialRHS(const Eigen::VectorXd& coeffs);
    /// Simple destructor
    virtual ~PolynomialRHS() {}
  private:
    Eigen::VectorXd coeffs_; //!< Coefficients defining the polynomial
};
#endif //POLYNOMIALRHS_H
