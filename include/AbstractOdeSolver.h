//
// Created by csy on 2024/11/22.
//

#ifndef ABSTRACTODESOLVER_H
#define ABSTRACTODESOLVER_H
#include <ostream>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <memory>
#include "ODERightHandSide.h"

/**
 *@file AbstractOdeSolver.h
 *@brief Base solver class
 * This is the base solver class
 */

class AbstractOdeSolver {
public:

    AbstractOdeSolver() : stepSize(0), initialTime(0), finalTime(0), initialValue(0), f_rhs(nullptr) {}
    virtual ~AbstractOdeSolver() {}

    // Setters

    void SetStepSize(double h) { stepSize = h; }
    void SetTimeInterval(double t0, double t1) { initialTime = t0; finalTime = t1; }
    void SetInitialValue(double y0) { initialValue = y0; }
    void SetRightHandSide(std::unique_ptr<ODERightHandSide> f) { f_rhs = std::move(f); }

    // Getters
    /// This is a final time accessor
    double GetFinalTime() const { return finalTime; }
    /// This is a initial time accessor
    double GetInitialTime() const { return initialTime; }
    /// This is a initial value (y0) accessor
    double GetInitialValue() const { return initialValue; }
    /// This is a step size accessor
    double GetStepSize() const { return stepSize; }

    // Solve the equation over the time interval
    virtual void SolveEquation(std::ostream& stream);

    // Result vector
    Eigen::VectorXd results;
    void PrintResults(std::ostream& stream) const;

protected:
    virtual double step(double y, double t) = 0; // Pure virtual step function
    std::unique_ptr<ODERightHandSide> f_rhs;
private:
    double stepSize;
    double initialTime;
    double finalTime;
    double initialValue;
};

#endif //ABSTRACTODESOLVER_H
