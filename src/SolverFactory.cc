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
}

// Factory method to create solvers
std::unique_ptr<AbstractOdeSolver> SolverFactory::createSolver(const SolverConfig& config) {
    config.validate();

    const auto& method = config.method;
    const auto& globalParams = config.globalParams;
    const auto& methodParams = config.methodParams;
    std::string initMethod = config.initMethod;
    int order = config.order;
    int steps = config.steps;

    std::unique_ptr<AbstractOdeSolver> solver;

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

    // Configure the solver
    configureGlobalParams(*solver, globalParams);

    return solver;
}

// Helper function to configure global parameters
void SolverFactory::configureGlobalParams(AbstractOdeSolver& solver, const std::map<std::string, double>& params) {
    if (params.count("stepSize")) solver.SetStepSize(params.at("stepSize"));
    if (params.count("t0") && params.count("t1")) solver.SetTimeInterval(params.at("t0"), params.at("t1"));
    if (params.count("initialValue")) solver.SetInitialValue(params.at("initialValue"));
}
