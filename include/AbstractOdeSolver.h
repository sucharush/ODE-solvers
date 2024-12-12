/**
 * @file AbstractOdeSolver.h
 * @brief Header file for the base solver class.
 * @author csy
 * @date 22.11.24.
 */

#ifndef ABSTRACTODESOLVER_H
#define ABSTRACTODESOLVER_H
#include <ostream>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <memory>
#include "ODERightHandSide.h"

//!  Base solver class.
/*!
This is the base solver class, that allows us to solve ODEs.
*/

class AbstractOdeSolver {
public:
    //! Default constructor for Abstract Solver.
    /*!
    This constructor sets all scalar parameters to 0, and initializes the right hand side to be a null pointer.
    */
    AbstractOdeSolver() : stepSize(0.0), initialTime(0.0), finalTime(0.0), initialValue(0.0), f_rhs(nullptr) {}
    /// Destructor for Abstract Solver.
    virtual ~AbstractOdeSolver() {}

    // Setters
    /// Sets the step size for the solver.
    void SetStepSize(double h) { stepSize = h; }
    /// Sets the initial and final time of the ODE.
    void SetTimeInterval(double t0, double t1) { initialTime = t0; finalTime = t1; }
    /// Sets the initial value of the ODE.
    void SetInitialValue(double y0) { initialValue = y0; }
    /// Sets the right hand side of the ODE
    void SetRightHandSide(std::unique_ptr<ODERightHandSide> f) { f_rhs = std::move(f); }

    // Getters
    /// This is a final time accessor.
    double GetFinalTime() const { return finalTime; }
    /// This is a initial time accessor.
    double GetInitialTime() const { return initialTime; }
    /// This is a initial value (y0) accessor.
    double GetInitialValue() const { return initialValue; }
    /// This is a step size accessor.
    double GetStepSize() const { return stepSize; }

    /// Solves the ODE.
    /*!
     *@param stream output stream to put the numerical solution.
     */
    virtual void SolveEquation(std::ostream& stream);

    /// Result vector.
    /*!
     * Vector member that stores the results of the solution of the ODE with the solver.
     */
    Eigen::VectorXd results;
    /// Method that outputs the result in the given stream.
    /*!
      @param stream output stream to put the results.
    */
    void PrintResults(std::ostream& stream) const;

protected:
    /// Protected (pure virtual) method that computes only one step of the scheme.
    /// This method is called iteratively to solve the ODE.
    /*!
    @param y space variable.
    @param t time variable.
    @see SolveEquation
    */
    virtual double step(double y, double t) = 0;
    std::unique_ptr<ODERightHandSide> f_rhs; //!< Right hand side of the ODE
private:
    double stepSize; //!< Step size for the solver
    double initialTime; //!< Initial time for the ODE
    double finalTime; //!< Final time for the ODE
    double initialValue; //!< Initial value of the ODE
};

#endif //ABSTRACTODESOLVER_H
