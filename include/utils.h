/**
 * @file utils.h
 * @brief Utility functions, type definitions and constants for the project.
 *
 * This header file contains:
 * - Commonly used type definitions (`typedef`) to simplify code readability.
 * - General-purpose utility functions (helpers) used throughout the project, reusable in different contexts.
 * - Constants variables shared across multiple modules.
 *
 * @author ebaup
 * @date 01.12.24.
 */

#ifndef UTILS_H
#define UTILS_H

#include <functional>

// Useful constants
// for newton
double const TOL = 1e-6;
double const MAX_ITER = 50;
// for error between numerical and analytical solutions
double const TOL_SOLUTION = 1e-2;
// Typedef for space variable type (y)
typedef double var_y; //TODO: change to Eigen::VectorXf, do we need the dimension as parameter in RHS?

// Typedef for function type
typedef std::function<double(double, double)> FuncType;

#endif //UTILS_H
