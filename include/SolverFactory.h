//
// Created by csy on 2024/12/8.
//

#ifndef SOLVERFACTORY_H
#define SOLVERFACTORY_H
#include <memory>
#include <map>
#include <string>
#include "AdamsBashforthSolver.h"
#include "BackwardEulerSolver.h"
#include "ForwardEulerSolver.h"
#include "RungeKuttaSolver.h"

struct SolverConfig {
    std::string method;
    std::map<std::string, double> globalParams;
    std::map<std::string, double> methodParams;
    int order = 4;           // defaulted order for Runge-Kutta
    std::string initMethod = "RK4";  // defaulted method for AB initialization
    int steps = 2;                   // default step for Adams-Bashforth

    void validate() const {
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
};

class SolverFactory {
public:
    static std::unique_ptr<AbstractOdeSolver> createSolver(const SolverConfig& config) {
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

        // build solver for other different methods
        if (method == "AB") {
            solver = std::make_unique<AdamsBashforthSolver>(steps, initMethod);
        } else if (method == "BE") {
            auto backwardEuler = std::make_unique<BackwardEulerSolver>();
            // optional parameters
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

        // configure the solver
        configureGlobalParams(*solver, globalParams);
//        configureMethodParams(*solver, methodParams);

        return solver;
    }

private:
    static void configureGlobalParams(AbstractOdeSolver& solver, const std::map<std::string, double>& params) {
        if (params.count("stepSize")) solver.SetStepSize(params.at("stepSize"));
        if (params.count("t0") && params.count("t1")) solver.SetTimeInterval(params.at("t0"), params.at("t1"));
        if (params.count("initialValue")) solver.SetInitialValue(params.at("initialValue"));
    }

};

#endif //SOLVERFACTORY_H
