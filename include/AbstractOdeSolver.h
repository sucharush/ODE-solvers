//
// Created by csy on 2024/11/22.
//

#ifndef ABSTRACTODESOLVER_H
#define ABSTRACTODESOLVER_H
#include <ostream>
#include "ODERightHandSide.h"

class AbstractOdeSolver {
public:
    // Constructor and destructor
    AbstractOdeSolver() : stepSize(0), initialTime(0), finalTime(0), initialValue(0), f_rhs(nullptr) {}
    virtual ~AbstractOdeSolver() {}

    // Setters
    void SetStepSize(double h) { stepSize = h; }
    void SetTimeInterval(double t0, double t1) { initialTime = t0; finalTime = t1; }
    void SetInitialValue(double y0) { initialValue = y0; }
    void SetRightHandSide(std::unique_ptr<ODERightHandSide> f) { f_rhs = std::move(f); }

    // Getters
    double GetFinalTime() const { return finalTime; }
    double GetInitialTime() const { return initialTime; }
    double GetInitialValue() const { return initialValue; }
    double GetStepSize() const { return stepSize; }

    // Solve the equation over the time interval
    void SolveEquation(std::ostream& stream);

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
