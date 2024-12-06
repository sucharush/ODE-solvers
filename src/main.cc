#include <iostream>
#include <memory>
#include <cmath>
#include "ForwardEulerSolver.h"
#include "BackwardEulerSolver.h"
#include "ModelProblemRHS.h"
#include "UnknownDerivativeRHS.cpp"
#include "AdamsBashforthSolver.h"
#include "RungeKuttaSolver.h"
#include "ImplicitSolver.cpp"

double computeAnalyticalSolution(double t, double y0, double k) {
    return y0 * std::exp(-k * t);
}

int main() {

    double initialTime = 0.0;
    double finalTime = 10.0;
    double initialValue = 1.0;
    double stepSize = 0.1;  // Change this as needed for accuracy
    double k = 0.3;  // Decay constant

    // Set up the right-hand side function
    std::unique_ptr<ODERightHandSide> rhs = std::make_unique<ModelProblemRHS>(k);

    // Set up the solver
    // ForwardEulerSolver solver;
    // AdamsBashforthSolver solver(4, "RK4");
    BackwardEulerSolver solver;
    solver.SetStepSize(stepSize);
    solver.SetTimeInterval(initialTime, finalTime);
    solver.SetInitialValue(initialValue);
    solver.SetRightHandSide(std::move(rhs));

    // Solve the ODE
    solver.SolveEquation(std::cout);  // Assuming SolveEquation outputs to a given stream
    solver.PrintResults(std::cout);
    double t = initialTime;
    int numSteps = solver.results.size();
    std::cout << "\nComparison with Analytical Solution:\n";
    std::cout << "t\tNumerical\tAnalytical\tError\n";

    for (int i = 0; i < numSteps; ++i, t += stepSize) {
        double numerical = solver.results[i];
        double analytical = computeAnalyticalSolution(t, initialValue, k);
        double error = std::abs(numerical - analytical);

        std::cout << t << "\t" << numerical << "\t" << analytical << "\t" << error << "\n";
    }



   //  FuncType func_test(
   //     [](double y, double t) { return y * y + std::cos(y)*t; } // f(y, t) = y^2 + t + cos(y)t
   // );
   //  UnknownDerivativeRHS F(func_test);
   //  FuncType Dfunc_test(
   //      [](double y, double t) { return 2 * y - std::sin(y)*t; } // df(y,t) = 2*y - sin(y)t
   //  );
   //  double t_ = 2.5;
   //  for (int i(0); i < 15; i++) {
   //      std::cout << "At (" <<i << ", "<< t_   << "), my der - true der =  " << F.derivative(i, t_) - Dfunc_test(i, t_) << std::endl;
   //  }
    return 0;
}
