//
// Created by ebaup on 07.12.24.
//

#include "UserDefinedRHS.h"

// UserDefinedRHS::UserDefinedRHS(): {
//     f = std::make_shared<FuncType>([this](double y, double t) { return -k*y; });
//     df = std::make_shared<FuncType>([k](double y, double /*t*/) { return 0.0; }); // derivative wrt t is 0
// }

UserDefinedRHS::UserDefinedRHS() {
    f = std::make_shared<FuncType>([this](double y, double t) {
        return 0;
    });
    // df = std::make_shared<FuncType>([this](double y, double t) {
    //     return 0;
    // });
}
