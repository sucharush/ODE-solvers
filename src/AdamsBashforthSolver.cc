//
// Created by csy on 2024/12/3.
//
#include "AdamsBashforthSolver.h"
#include <iostream>

AdamsBashforthSolver::AdamsBashforthSolver(int order_, const std::string& init_method_):
  order_(order_), init_method_(init_method_) {
  if (order_ < 2 || order_ > 4) {
    throw std::invalid_argument("Adams-Bashforth method order must be between 2 and 4.");
  }
  if (init_method_ != "FE" && init_method_ != "RK4") {
    throw std::invalid_argument("Initialization method must be \"FE\" or \"RK4\".");
  }
}
AdamsBashforthSolver::~AdamsBashforthSolver() {}

double AdamsBashforthSolver::step(double y, double t){
  double initialTime = GetInitialTime();
  double stepSize = GetStepSize();
  int currentStep = static_cast<int>((t - initialTime)/stepSize);
  double nextY = y;

  if (currentStep < order_ - 1){
    // use forward Euler if the steps are not enough
    if (init_method_ == "FE") {
      nextY += stepSize * f_rhs->value(y, t);
    } else {
      double k1 = stepSize * f_rhs->value(y, t);
      double k2 = stepSize * f_rhs->value(y + 0.5 * k1, t + 0.5 * stepSize);
      double k3 = stepSize * f_rhs->value(y + 0.5 * k2, t + 0.5 * stepSize);
      double k4 = stepSize * f_rhs->value(y + k3, t + stepSize);
      nextY = y + (k1 + 2 * k2 + 2 * k3 + k4) / 6.0;
    }

  } else{
    // std::cout<<"real step: " << (t - initialTime)/stepSize << " step: " <<
    //   currentStep << " current: " << results[currentStep] << " y: " << y << std::endl;
    double sum = 0;
    static const double coefficients[3][4] = {
      {3.0 / 2.0, -1.0 / 2.0, 0.0, 0.0},        // Order 2
      {23.0 / 12.0, -16.0 / 12.0, 5.0 / 12.0}, // Order 3
      {55.0 / 24.0, -59.0 / 24.0, 37.0 / 24.0, -9.0 / 24.0} // Order 4
    };
    for (int i = 0; i < order_; ++i){
      sum += coefficients[order_ - 2][i] * f_rhs->value(results[currentStep - i], t-i*stepSize);
    }
    nextY += stepSize * sum;
  }
  return nextY;
}