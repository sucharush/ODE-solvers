/**
 * @file RungeKuttaSolver.h
 * @brief Runge Kutta solver.
 * @author csy
 * @date 29.11.24.
 */

#ifndef RUNGEKUTTASOLVER_H
#define RUNGEKUTTASOLVER_H

#include <iostream>
#include "ExplicitSingleStepSolver.h"

//! Class for Runge Kutta solvers

class RungeKuttaSolver: public ExplicitSingleStepSolver {
public:
    /// Constructor
    /*! This constructor sets the order of the RUnge Kutta method.
     @param order order of the method
     */
    explicit RungeKuttaSolver(const int order): order_(order){}
    /// Simple  destructor
    virtual ~RungeKuttaSolver() {}
    /// This sets the order of the solver
    void SetType(const int order) {order_ = order;};
    /// This is a simple accessor to the order
    int GetType() const {return order_;};

  protected:
    double step(double y, double t) override;
  private:
    int order_; //!< Order of the Runge Kutta scheme
};
#endif //RUNGEKUTTASOLVER_H
