//
// Created by csy on 2024/11/29.
//

#ifndef BUTCHERTABLE_H
#define BUTCHERTABLE_H
#include <unordered_map>
#include <vector>
#include <Eigen/Dense>

struct ButcherTableau {
    std::vector<double> c;            // Nodes (time coefficients)
    Eigen::MatrixXd a;                // Intermediate coefficients matrix
    std::vector<double> b;            // Weight coefficients for the final sum
};

ButcherTableau getButcherTableau(const std::string& method) {
    if (method == "RK2") {
        return {
                {0.0, 0.5}, // c values
                (Eigen::MatrixXd(2, 2) << 0.0, 0.0, 0.5, 0.0).finished(), // a matrix
                {0.0, 1.0} // b values
        };
    } else if (method == "RK4") {
        return {
                {0.0, 0.5, 0.5, 1.0}, // c values
                (Eigen::MatrixXd(4, 4) << 0.0, 0.0, 0.0, 0.0,
                                          0.5, 0.0, 0.0, 0.0,
                                          0.0, 0.5, 0.0, 0.0,
                                          0.0, 0.0, 1.0, 0.0).finished(), // a matrix
                {1.0/6.0, 1.0/3.0, 1.0/3.0, 1.0/6.0} // b values
        };
        // Here to add Runge-Kutta with other orders
    } else {
        throw std::invalid_argument("Unsupported method: " + method +
            "Please choose from 'RK2', 'RK4' ");
    }
}

#endif //BUTCHERTABLE_H
