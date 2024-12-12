//
// Created by csy on 2024/12/12.
//

#ifndef POLYNOMIALRHS_H
#define POLYNOMIALRHS_H
#include "KnownDerivativeRHS.h"
#include <Eigen/Dense>

class PolynomialRHS : public KnownDerivativeRHS {
  public:
    explicit PolynomialRHS(const Eigen::VectorXd& coeffs);
    virtual ~PolynomialRHS() {}
  private:
    Eigen::VectorXd coeffs_;
};
#endif //POLYNOMIALRHS_H
