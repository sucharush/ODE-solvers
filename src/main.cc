#include <iostream>
#include <memory>
#include <cmath>
#include "ForwardEulerSolver.h"
#include "ModelProblemRHS.h"

int main() {
    double initialTime = 0.0;
    double finalTime = 10.0;
    double initialValue = 1.0;
    double stepSize = 0.1;  // Change this as needed for accuracy
    double k = 0.3;  // Decay constant

    // Set up the right-hand side function
    std::unique_ptr<ODERightHandSide> rhs = std::make_unique<ModelProblemRHS>(k);

    // Set up the solver
    ForwardEulerSolver solver;
    solver.SetStepSize(stepSize);
    solver.SetTimeInterval(initialTime, finalTime);
    solver.SetInitialValue(initialValue);
    solver.SetRightHandSide(std::move(rhs));

    // Solve the ODE
    solver.SolveEquation(std::cout);  // Assuming SolveEquation outputs to a given stream

    return 0;
}
