/**
 * @file ConfigParser.h
 * @brief Configuration parser
 * @author csy
 * @date 08.12.24.
 */

#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <string>
#include "SolverFactory.h"

//! Class for configuration parsers

class ConfigParser {
public:
    /// Method to initialize a solver configuration from a file
    static SolverConfig parseConfig(const std::string& filePath);
};

#endif //CONFIGPARSER_H
