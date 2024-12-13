//
// Created by csy on 2024/12/12.
//
#include "PolynomialRHS.h"
#include "KnownDerivativeRHS.h"
#include <Eigen/Dense>
#include <functional>



PolynomialRHS::PolynomialRHS(const Eigen::VectorXd& coeffs):KnownDerivativeRHS(), coeffs_(coeffs){
    f = std::make_shared<FuncType>([this](double y, double /*t*/) -> double {
        // f = a_n*y^n + ... + a_1*y + a_0 = (...((a_n*y + a_{n-1})*y + a_{n-1})*y +...+a_1)*y + a_0
        double result = coeffs_(coeffs_.size() - 1);
        for (int i = coeffs_.size() - 2; i >= 0; --i) {
            result = result * y + coeffs_(i);
        }
        return result;
    });
    df = std::make_shared<FuncType>([this](double y, double /*t*/) -> double {
        if (coeffs_.size() == 1) {
          return 0.0;
        }
        double result = coeffs_(coeffs_.size() - 1) * (coeffs_.size() - 1); // n*a_n
        for (int i = coeffs_.size() - 2; i > 0; --i) {
            result = result * y + i * coeffs_(i);
        }
        return result;
    });
}
