/**
 * @file ImplicitSolver.h
 * @brief Implicit solver class.
 * @author ebaup
 * @date 06.12.24.
 */
#ifndef IMPLICITSOLVER_H
#define IMPLICITSOLVER_H

#include "AbstractOdeSolver.h"
#include "utils.h"

//!  (Abstract) class for implicit solvers.

class ImplicitSolver : public AbstractOdeSolver {
public:
    /// Simple constructor
    /*!
    This constructor sets the tolerance and maximum iterations variable, and use default parameters if they are unspecified.
    @param tol tolerance criteria for Newton's method, default: TOL (1e-6)
    @param n_max maximum iterations for Newton's method, default: MAX_ITER (50)
    @see utils.h for the default parameters
    */
    ImplicitSolver(double tol = TOL, double n_max = MAX_ITER);
    // Setters for the private parameters
    /// Sets the tolerance criteria for Newton
    void SetTolerance(double tol);
    /// Sets the maximum iteration number for Newton
    void SetMaxIter(double n_max);
    // TODO: do we need getters?
protected:
    virtual double step(double y, double t) = 0;
    //! Newton's method
    /*!
    This method implements Newton's algorithm for finding the zero of the following function:
    g(x) = x - yn - h*f(x, t_{n+1}),
    which is equivalent to solving y_{n+1} = y_n + h*f(y_{n+1}, t_{n+1}).
    @param yn the current approximation of y(t_n)
    @param tn1 the time variable t_{n+1} = t0 + n*h
    */
    double newton(double yn, double tn1);
private:
    double tolerance; //!< tolerance criteria for Newton's method
    double max_iter; //!< maximum iteration number for Newton's method
};
#endif //IMPLICITSOLVER_H
