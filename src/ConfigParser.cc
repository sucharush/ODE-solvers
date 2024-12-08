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

    return config;
}

