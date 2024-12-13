
cmake_minimum_required (VERSION 3.0)
project (PCSC-project)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)
include_directories(src)


add_library(solvers
        src/AbstractOdeSolver.cc
        src/AdamsBashforthSolver.cc
        src/BackwardEulerSolver.cc
        src/ForwardEulerSolver.cc
        src/RungeKuttaSolver.cc
        src/ExplicitMultiStepSolver.cc
        src/ImplicitSolver.cc
        src/ConfigParser.cc
        src/SolverFactory.cc
)
add_library(rhs
        src/KnownDerivativeRHS.cc
        src/ODERightHandSide.cc
        src/UnknownDerivativeRHS.cc
        src/PolynomialRHS.cc
        src/ModelProblemRHS.cc
)

add_subdirectory(eigen)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/eigen)

add_executable(main main.cc)
target_link_libraries(main solvers rhs)

option(DOCUMENTATION "Activate documentation" ON)
if (DOCUMENTATION)
    set(DOXYGEN_EXECUTABLE doxygen)
    set(DOXYFILE Doxyfile)
    add_custom_target(doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/${DOXYFILE}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
endif(DOCUMENTATION)

set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
option(TESTS "Activate tests" ON)
if (TESTS)
    add_subdirectory(googletest)
    add_executable(tests ${TEST_DIR}/auxiliary_test.cc ${TEST_DIR}/model_problem_test.cc ${TEST_DIR}/polynomial_test.cc)
    target_link_libraries(tests gtest_main gtest pthread solvers rhs)

    add_custom_target(test
            COMMAND tests
            WORKING_DIRECTORY ${CMAKE_CURRENT_BUILD_DIR}
            COMMENT "Running tests")
endif(TESTS)