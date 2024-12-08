//
// Created by csy on 2024/12/8.
//

#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <string>
#include "SolverFactory.h"

class ConfigParser {
public:
    static SolverConfig parseConfig(const std::string& filePath);
};

#endif //CONFIGPARSER_H
