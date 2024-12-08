//
// Created by csy on 2024/11/29.
//

#ifndef RUNGEKUTTASOLVER_H
#define RUNGEKUTTASOLVER_H

#include <iostream>
#include "ExplicitSingleStepSolver.h"

class RungeKuttaSolver: public ExplicitSingleStepSolver {
  public:
    explicit RungeKuttaSolver(const int order): order_(order){};
    virtual ~RungeKuttaSolver() {};
    // setter and getter
    void SetType(const int order) {order_ = order;};
    int GetType() const {return order_;};

  protected:
    double step(double y, double t) override;
  private:
    int order_;
};
#endif //RUNGEKUTTASOLVER_H
