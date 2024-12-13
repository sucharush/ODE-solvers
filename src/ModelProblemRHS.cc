//
// Created by csy on 2024/12/12.
//
#include "ModelProblemRHS.h"
ModelProblemRHS::ModelProblemRHS(double k): k_(k){
    f = std::make_shared<FuncType>([k](double y, double /*t*/) { return -k*y; });
    df = std::make_shared<FuncType>([k](double y, double /*t*/) { return 0.0; }); // derivative wrt t is 0
}