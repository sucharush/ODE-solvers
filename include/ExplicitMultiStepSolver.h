/**
 * @file ExplicitMultiStepSolver.h
 * @brief Explicit multi-step solvers.
 * @author csy
 * @date 05.12.24.
 */
#ifndef EXPLICITMULTISTEPSOLVER_H
#define EXPLICITMULTISTEPSOLVER_H

#include <Eigen/Dense>
#include "ExplicitSolver.h"
#include "ExplicitSingleStepSolver.h"
#include <iostream>

//! (Abstract) class for explicit multi-step solvers

class ExplicitMultiStepSolver : public ExplicitSolver {
public:
    /// Constructor
    /*!
    This constructor sets the order and initial method of an explicit multi-step solver.
    @param steps order of the solver
    @param initMethod initial method to compute the initial values
    */
    ExplicitMultiStepSolver(int steps, const std::string &initMethod);
    /// Simple destructor
    virtual ~ExplicitMultiStepSolver();
    /// This sets the order of the solver
    void setSteps(int steps);
    /// This sets the initial auxiliary method to compute the initial values
    void setInitMethod(const std::string &initMethod);
    /// This is an accessor to the steps number of the solver (its order)
    int getSteps() const;
    /// This is an accessor to the initial method
    std::string getInitMethod() const;
    /// Overriden implementation of the solver
    /*! The solver begins by calculating the initial values with an auxiliary method (initial method).
     Then the rest of the solution is found recursively as usual.
     */
    virtual void SolveEquation(std::ostream& stream) override;

protected:
    virtual double step(double y, double t) = 0;
    Eigen::VectorXd coeffs_; //!< Coefficients (weights) that determine the method.

private:
    int steps_; //!< Number of steps of the method (order)
    std::string initMethod_; //!< Auxiliary method used for the computation of the initial values of the solution
};
#endif //EXPLICITMULTISTEPSOLVER_H
