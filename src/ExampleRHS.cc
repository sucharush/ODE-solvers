//
// Created by ebaup on 07.12.24.
//

#include "ExampleRHS.h"

ExampleRHS::ExampleRHS(double k): k_(k){
    f = std::make_shared<FuncType>([k](double y, double /*t*/) { return -k*y; });
    df = std::make_shared<FuncType>([k](double y, double /*t*/) { return 0.0; }); // derivative wrt t is 0
}