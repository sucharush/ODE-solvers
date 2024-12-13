/**
 * @file utils.h
 * @brief Type definitions and constants for the project.
 *
 * This header file contains:
 * - Commonly used type definitions (`typedef`) to simplify code readability.
 * - Constants variables shared across multiple modules.
 *
 * @author ebaup
 * @date 01.12.24.
 */

#ifndef UTILS_H
#define UTILS_H

#include <functional>
#include <cmath>
// Useful constants
double const TOL = 1e-6; //!< Default tolerance threshold (for Newton and difference scheme)
double const MAX_ITER = 50; //!< Default maximum number of iterations for Newton method

double const TOL_SOLUTION = 1e-2; //!< Tolerance threshold for error

double const TOL_EQ = 1e-8; //!< Tolerance threshold for double comparison

typedef double var_y; //!< [unused] Typedef for the space parameter of the ODE

/// Typedef for function type (right hand side object of the ODE)
typedef std::function<double(double, double)> FuncType;


#endif //UTILS_H
