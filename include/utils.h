/**
 Created by ebaup on 01.12.24.
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

// Typedef for space variable type (y)
typedef double var_y; //TODO: change to Eigen::VectorXf, do we need the dimension as parameter in RHS?

// Typedef for function and derivative type
typedef std::function<double(double, double)> FuncType;
typedef std::function<double(double, double)> DerivativeType; // TODO: do we use it?



#endif //UTILS_H
