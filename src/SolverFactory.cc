//
// Created by csy on 2024/12/9.
//
#include "SolverFactory.h"

// Validate the configuration
void SolverConfig::validate() const {
    if (globalParams.count("stepSize") == 0 ||
        globalParams.count("t0") == 0 ||
        globalParams.count("t1") == 0 ||
        globalParams.count("initialValue") == 0) {
        throw std::invalid_argument("Missing required global parameters: stepSize, t0, t1, initialValue.");
    }
    if (method.empty()) {
        throw std::invalid_argument("Solver method must be specified.");
    }
    if (type.empty()) {
        throw std::invalid_argument("Right hand side function type must be specified.");
    }
};

// Factory method to create solvers
std::unique_ptr<AbstractOdeSolver> SolverFactory::createSolver(const SolverConfig& config) {
    config.validate();

    const auto& method = config.method;
    const auto& globalParams = config.globalParams;
    const auto& methodParams = config.methodParams;
    std::string initMethod = config.initMethod;
    int order = config.order;
    int steps = config.steps;
    std::string type = config.type;
    double decay = config.decay;
    Eigen::VectorXd coeffs = config.coefficients;

    std::unique_ptr<AbstractOdeSolver> solver;
    std::unique_ptr<ODERightHandSide> rhs;

    // ForwardEuler fallback
    if ((method == "RK" && order == 1) ||
        (method == "AB" && steps == 1)) {
        std::cout << "Note: Falling back to Forward Euler Solver." << std::endl;
        return std::make_unique<ForwardEulerSolver>();
    }

    // Build solver for different methods
    if (method == "AB") {
        solver = std::make_unique<AdamsBashforthSolver>(steps, initMethod);
    } else if (method == "BE") {
        auto backwardEuler = std::make_unique<BackwardEulerSolver>();
        // Optional parameters
        if (methodParams.count("tolerance")) {
            backwardEuler->SetTolerance(methodParams.at("tolerance"));
        }
        if (methodParams.count("maxIter")) {
            backwardEuler->SetMaxIter(methodParams.at("maxIter"));
        }
        solver = std::move(backwardEuler);
    } else if (method == "FE") {
        solver = std::make_unique<ForwardEulerSolver>();
    } else if (method == "RK") {
        solver = std::make_unique<RungeKuttaSolver>(order);
    } else {
        throw std::invalid_argument("Unsupported solver method: " + method
                                    + ". Supported methods are: AB (AdamsBashforth), BE (BackwardEuler), FE (ForwardEuler), RK (RungeKutta).");
    }
    // build rhs functions
    if (type == "model") {
        // std::cout << "rhs type: " << type << "." << std::endl;
        rhs = std::make_unique<ModelProblemRHS>(decay);
    } else if (type == "poly") {
        // std::cout << "rhs type: " << type << "." << std::endl;
        if (coeffs.size() == 0) {
            throw std::invalid_argument("Polynomial coefficients must be provided for 'poly' rhs type.");
        }
        rhs = std::make_unique<PolynomialRHS>(coeffs);
    } else {
        throw std::invalid_argument("Unsupported rhs type: " + type);
    }
    // Set rhs
    solver->SetRightHandSide(std::move(rhs));

    // Configure the solver
    // Configure global parameters directly here
    if (globalParams.count("stepSize")) {
        solver->SetStepSize(globalParams.at("stepSize"));
    }
    if (globalParams.count("t0") && globalParams.count("t1")) {
        solver->SetTimeInterval(globalParams.at("t0"), globalParams.at("t1"));
    }
    if (globalParams.count("initialValue")) {
        solver->SetInitialValue(globalParams.at("initialValue"));
    }

    return solver;
}

