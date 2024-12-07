//
// Created by csy on 2024/12/5.
//

#ifndef EXPLICITMULTISTEPSOLVER_H
#define EXPLICITMULTISTEPSOLVER_H

#include <Eigen/Dense>
#include "ExplicitSolver.h"
#include "ExplicitSingleStepSolver.h"
#include <iostream>

class ExplicitMultiStepSolver : public ExplicitSolver {
  public:
    ExplicitMultiStepSolver(int steps, const std::string &initMethod);
    virtual ~ExplicitMultiStepSolver();
    void setSteps(int steps);
    void setInitMethod(const std::string &initMethod);
    int getSteps() const;
    std::string getInitMethod() const;
    virtual void SolveEquation(std::ostream& stream) override;

  protected:
    virtual double step(double y, double t) = 0;
    Eigen::VectorXd coeffs_;

  private:
    void setupSolver(ExplicitSingleStepSolver& solver);
    int steps_;
    std::string initMethod_;
};
#endif //EXPLICITMULTISTEPSOLVER_H
