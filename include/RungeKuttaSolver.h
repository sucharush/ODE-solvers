//
// Created by csy on 2024/11/29.
//
#include <iostream>
#include "ExplicitSingleStepSolver.h"
#ifndef RUNGEKUTTASOLVER_H
#define RUNGEKUTTASOLVER_H
class RungeKuttaSolver: public ExplicitSingleStepSolver {
  public:
    RungeKuttaSolver(): type_("RK4"){}; // set RK4 as default
    virtual ~RungeKuttaSolver() {};
    // setter and getter
    void SetType(const std::string& type);
    const std::string& GetType() const;

  protected:
    virtual double step(double y, double t);
    std::string type_;
};
#endif //RUNGEKUTTASOLVER_H
