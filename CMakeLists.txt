
cmake_minimum_required (VERSION 3.0)
project (PCSC-project)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)
include_directories(src)

add_library(ode_solver src/AbstractOdeSolver.cc)
add_library(fe_solver src/ForwardEulerSolver.cc)
add_library(rk_solver src/RungeKuttaSolver.cc)
add_library(ab_solver src/AdamsBashforthSolver.cc)
add_library(ex_multi_solver src/ExplicitMultiStepSolver.cc)
add_library(be_solver src/BackwardEulerSolver.cpp)

add_subdirectory(eigen)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/eigen)

add_executable(main src/main.cc)
target_link_libraries(main ode_solver fe_solver rk_solver ab_solver ex_multi_solver be_solver)

set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
option(TESTS "Activate tests" OFF)
if (TESTS)
    add_subdirectory(googletest)
    add_executable(tests ${TEST_DIR}/test.cc ${TEST_DIR}/model_problem_test.cpp)
    target_link_libraries(tests gtest_main gtest pthread)

    add_custom_target(test
            COMMAND tests
            WORKING_DIRECTORY ${CMAKE_CURRENT_BUILD_DIR}
            COMMENT "Running tests")
endif(TESTS)