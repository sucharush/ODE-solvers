
cmake_minimum_required (VERSION 3.0)
project (PCSC-project)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)


add_library(ode_solver src/AbstractOdeSolver.cc
)
add_library(fe_solver src/ForwardEulerSolver.cc
)

add_subdirectory(googletest)

add_executable(main src/main.cc)
target_link_libraries(main ode_solver fe_solver)

add_executable(test_pcsc test/test.cc)
target_link_libraries(test_pcsc gtest_main gtest pthread)

add_custom_target(test ./test_pcsc DEPENDS test_pcsc)
