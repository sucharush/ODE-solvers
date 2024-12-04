//
// Created by csy on 2024/11/29.
//
#include "RungeKuttaSolver.h"
#include "ButcherTable.h"


double RungeKuttaSolver::step(double y, double t){

  // get Butcher tableau
  std::string method = type_;
  ButcherTableau tableau = getButcherTableau(method);

  int s = tableau.c.size();
  Eigen::VectorXd k(s);
  double h = GetStepSize();

  for (int i = 0; i < s; ++i){

    double ti = t + tableau.c[i]*h;
    double yi = y;
    for (int j = 0; j < i; ++j){
      yi += h*tableau.a(i, j)*k[j];
    }

    k[i] = f_rhs->value(yi, ti);
  }
  double nextY = y;
  for (int i = 0; i < s; ++i){
    nextY += h*tableau.b[i]*k[i];
  }
  return nextY;
}

void RungeKuttaSolver::SetType(const std::string &type) {
  type_ = type;
}

const std::string &RungeKuttaSolver::GetType() const {
  return type_;
}
