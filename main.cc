#include <iostream>
#include <filesystem>
#include <fstream>
#include <memory>
#include <cmath>
#include "include/ForwardEulerSolver.h"
#include "include/BackwardEulerSolver.h"
#include "src/ODERightHandSide.cc"
#include "src/KnownDerivativeRHS.cc"
#include "include/AdamsBashforthSolver.h"
#include "include/RungeKuttaSolver.h"
#include "src/ImplicitSolver.cc"
#include "src/ModelProblemRHS.cc"
#include "src/PolynomialRHS.cc"
#include "ConfigParser.h"
#include "UserDefinedRHS.h"
#include "SolverFactory.h"


int main() {
    try {
        std::filesystem::path projectRoot = std::filesystem::current_path().parent_path();
        std::filesystem::path configPath = projectRoot / "config" / "config.json";
        if (!std::filesystem::exists(configPath)) {
            throw std::runtime_error("Could not find configuration file: " + configPath.string());
        }
        SolverConfig config = ConfigParser::parseConfig(configPath.string());
        auto solver = SolverFactory::createSolver(config);

        // solve equation
        solver->SolveEquation(std::cout);

        // generate output file from result
        Eigen::VectorXd results = solver -> results;
        std::filesystem::path outputPath = projectRoot / "output.txt";
        std::ofstream outputFile(outputPath);
        outputFile << std::fixed << std::setprecision(4);
        if (!outputFile.is_open()) {
            std::cerr << "Could not open output file " << outputPath.string() << std::endl;
            return 1;
        }
        for (int i = 0; i < results.size(); i++) {
            outputFile << results[i] << std::endl;
        }
        outputFile.close();
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
