/**
 * @file ButcherTableau.h
 * @brief Butcher Tableau (for Runge-Kutta method)
 * @author csy
 * @date 29.12.24.
 */

#ifndef BUTCHERTABLE_H
#define BUTCHERTABLE_H

#include <unordered_map>
#include <vector>
#include <Eigen/Dense>

//! Structure for Butcher Tableau for the Runge Kutta method
/*!
 A Butcher tabeau stores the weights that determine a Runge-Kutta method.
 */
struct ButcherTableau {
    std::vector<double> c;            //!< Nodes (time coefficients)
    Eigen::MatrixXd a;                //!< Intermediate coefficients matrix
    std::vector<double> b;            //!< Weight coefficients for the final sum
};

/// Function to initializer a Butcher tableau
/*!
 This function initializes a Butcher tableau for the associated RK method.
 @param order order of the associated Runge-Kutta method
 */
ButcherTableau getButcherTableau(const int order) {
    if (order == 2) {
        return {
                {0.0, 0.5}, // c values
                (Eigen::MatrixXd(2, 2) << 0.0, 0.0, 0.5, 0.0).finished(), // a matrix
                {0.0, 1.0} // b values
        };
    } else if (order == 4) {
        return {
                {0.0, 0.5, 0.5, 1.0}, // c values
                (Eigen::MatrixXd(4, 4) << 0.0, 0.0, 0.0, 0.0,
                                          0.5, 0.0, 0.0, 0.0,
                                          0.0, 0.5, 0.0, 0.0,
                                          0.0, 0.0, 1.0, 0.0).finished(), // a matrix
                {1.0/6.0, 1.0/3.0, 1.0/3.0, 1.0/6.0} // b values
        };
        // Here we can add more tables for different orders
    } else {
        throw std::invalid_argument("Unsupported order: " + std::to_string(order) +
            "Please choose from 'RK2', 'RK4' ");
    }
}

#endif //BUTCHERTABLE_H
