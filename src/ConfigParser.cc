//
// Created by csy on 2024/12/8.
//
#include "ConfigParser.h"
#include <fstream>
#include "json.hpp"
#include <stdexcept>

SolverConfig ConfigParser::parseConfig(const std::string& filePath) {
    std::ifstream configFile(filePath);
    if (!configFile) {
        throw std::runtime_error("Could not open configuration file: " + filePath);
    }

    nlohmann::json configJson;
    configFile >> configJson;

    SolverConfig config;

    // global parameters
    for (const auto& [key, value] : configJson["global"].items()) {
        config.globalParams[key] = value;
    }

    // solver specific parameters
    config.method = configJson["solver"]["method"];
    for (const auto& [key, value] : configJson["solver"]["parameters"].items()) {
        if (key == "steps") {
            config.steps = static_cast<int>(value);
        } else if (key == "order") {
            config.order = static_cast<int>(value);
        } else if (key == "initMethod") {
            config.initMethod = value;
        } else {
            config.methodParams[key] = value;
        }
    }

    config.type = configJson["rhs"]["type"];
    for (const auto& [key, value] : configJson["rhs"]["parameters"].items()) {
        if (key == "decay") {
            config.decay = value.get<double>();
        }
        if (key == "coefficients") {
            std::vector<double> coeffs;
            for (const auto& coeff : value) {
                coeffs.push_back(coeff.get<double>());
            }
            config.coefficients = Eigen::VectorXd::Map(coeffs.data(), coeffs.size());
        }
    }


    return config;
}

