//
// Created by csy on 2024/12/3.
//
#include "AbstractOdeSolver.h"

#ifndef ADAMBASHFORTHSOLVER_H
#define ADAMBASHFORTHSOLVER_H
class AdamsBashforthSolver: public AbstractOdeSolver {
  public:
    AdamsBashforthSolver(int order_, const std::string& init_method_);
    virtual ~AdamsBashforthSolver();
  protected:
    virtual double step(double y, double t) override;
  private:
    int order_;
    std::string init_method_;
};
#endif //ADAMBASHFORTHSOLVER_H
