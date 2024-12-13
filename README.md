# Solvers for Ordinary Differential Equations
Project for MATH-458 Programming concepts in scientific computing (EPFL, 2024).
## Team members
- Ezra Baup, estelle.baup@epfl.ch
- Siyuan Cheng, siyuan.cheng@epfl.ch

## Table of contents
- [Project Overview](#project-overview)
- [How to](#how-to)
- [Features](#features)
- [Limitations](#limitations)

## Disclaimer for latex
The latex configuration is not entirely set for the Doxygen page, please use the preview on your editor or the preview from the Gitlab website to read the formulas easier.

## Project Overview
This project provides an implementation of numerical solvers for solving ordinary differential equations (ODEs), 
i.e. $y^{'}(t)=f(t,y(t))$. The solvers currently support the following methods:

- **Forward Euler (FE)**: Explicit single-step solver.
- **Runge-Kutta (RK)**: Explicit single-step solver supporting orders 1 through 4.
- **Adams-Bashforth (AB)**: Explict multistep solver with configurable order and initialization method (e.g., RK4, Forward Euler).
- **Backward Euler (BE)**: Implicit single-step solver with optional tolerance and iteration settings.

The default implementation solves the model problem $y^{'} = -0.3y$ using a 4th-order Runge-Kutta method. 
The project is modular, allowing customization of solvers, functions, and configurations.
### Right-Hand Side (RHS) Functions
To represent the right-hand side function $f(t, y)$ in the ODE, the project provides the following built-in options:

1. **Model Problem (`model`)**:
    - Describes a simple exponential decay problem $f(t, y) = -k \cdot y$.
    - Requires a positive decay constant `decay = k`.
    - Given the initial condition $y(t) = y_0$, the analytical solution is $y(t) = y_0 e^{-k(t-t_0)}.$

2. **Polynomial Function (`poly`)**:
    - Describes a polynomial of the form $f(t, y) = a_0 + a_1 y + a_2 y^2 + \dots + a_n y^n$.
    - Requires a list of coefficients `[a_0, a_1, ..., a_n]`.

These RHS functions can be selected and configured in the configuration file (`config/config.json`), providing flexibility for different types of ODEs. 
You can also implement custom RHS functions by modifying the `UserDefineRHS` classes.

## Structure
The main structure of the project is as follows:
- `/config`: configuration settings to run the main.
- `/include`: contains all header files.
- `/src`: contains all implementation files.
- `/test`: contains test files, supported by googletest.

[//]: # (The detailed structure of the project is shown below.)
```
    pcsc-project/
    ├── config/
    │   └── config.json                               // Configuration settings
    ├── include/
    │   ├── AbstractOdeSolver.h                       // Base class for all solvers
    │   ├── AdamsBashforthSolver.h                    
    │   ├── BackwardEulerSolver.h                    
    │   ├── ButcherTableau.h                          // For Runge-Kutta
    │   ├── ConfigParser.h                           
    │   ├── ExampleRHS.h                              
    │   ├── ExplicitMultiStepSolver.h                 // Extends ExplicitSolver to multi-step
    │   ├── ExplicitSingleStepSolver.h                // Extends ExplicitSolver to single-step
    │   ├── ExplicitSolver.h                          // Base class for all explicit solvers
    │   ├── ForwardEulerSolver.h                    
    │   ├── ImplicitSolver.h                          // Base class for implicit solvers
    │   ├── json.hpp                      
    │   ├── KnownDerivativeRHS.h                      // RHS with analytically known derivative
    │   ├── ModelProblemRHS.h
    │   ├── ODERightHandSide.h                        // Base class for RHS functions
    │   ├── PolynomialRHS.h
    │   ├── RungeKuttaSolver.h                       
    │   ├── SolverFactory.h                           
    │   └── UnknownDerivativeRHS.h                    // RHS with unknown derivative 
    ├── src/
    │   └── [Corresponding .cc files implementing the headers]
    ├── test/
    │   └── [Test files using googletest]
    ├── .gitignore
    ├── .gitmodules
    ├── main.cc     
    ├── CMakeLists.txt                                
    └── README.md                          
```
Here is a brief sketch of the class hierarchy.

<img src="hierarchy.png" alt="UML Diagram" width="700">

## How to
### Quick Start
First, you need to clone the project repository on your local machine.
```
git clone git@gitlab.epfl.ch:ebaup/pcsc-project.git
cd pcsc-project
```
### Set-up and Building
The project relies on *googletest* and *Eigen*, initialize them as submodules to install these dependencies:

```
git submodule update --init 
```

You can build and run the project using your preferred IDE (e.g., CLion) or the terminal. Below are the steps for the terminal:

```
mkdir build
cd build
cmake ..
make
./main
```
Building should output all the process, in particular the documentation generation prints a lot of indications about the status but you don't need to worry about that.
The main doesn't print anything, but generate an output file containing the solution.

### Read the output file
```
cd ..
cat output.txt
```

###  Update the Configuration
Modify the `config/config.json` file to set global parameters and solver-specific options. 
```
{
  "global": {
    "stepSize": The time step for the solver, e.g., 0.01,
    "t0": Start time of the simulation, e.g., 0.0,
    "t1": End time of the simulation, e.g., 1.0,
    "initialValue": Initial guess y_0, e.g., 1.0
  },
  "solver": {
    "method": Solver type, choose from {"RK", "AB", "BE", "FE"},
    "parameters": {
      "order": For Runge Kutta, choose from {1, 2, 4},
      "steps": For AdamsBashforth, choose from {1, 2, 3, 4},
      "initMethod": For AdamsBashforth, choose from {"RK4", "FE"},
      "tolerance": For Newton method in Backward Euler, default 1e-6,
      "maxIter": For Newton method in Backward Euler, default 50
    }
  },
  "rhs": {
    "type": RHS type, choose from {"model", "poly"},
    "parameters": {
      "decay": Decay constant for model problem, e.g., 0.1,
      "coefficients": For polynomials, a list of coefficients [a_0, a_1, ..., a_n]
    }
  }
}
```
**Note:** It will automatically build the forward Euler method when choosing `order = 1` for Runge Kutta or `steps = 1` for AdamsBashforth, as they are the same solvers.

### Documentation
Building the project also creates a folder 'doc', that contains the doxygen documentation of the project. To see this documentation, there are a few alternatives:
- open the file 'index.html' located in doc/html/. This should open a window in your browser with our documentation.
- use doxywizard (type `doxywizard` in your terminal) and select the Doxyfile located in the main folder of the project. Then you can run doxygen from doxywizard to generate the documentation.

### Tests
Another executive file produced by the building concerns the googletests. They are separated in 3 files:
- `auxiliary_test.cc`: contains tests on auxiliary classes, mainly on the function class.
- `model_problem_test.cc`: contains tests focusing on the model problem. In each execution of this test, a random variable between 0 and 1 is produced, and then all solvers are tested on the model problem defined by this variable.
- `polynomial_test.cc`: contains tests on a specific polynomial function, for all solvers.

All tests that consist of testing the solvers rely on testing the difference between the analytical solution and the approximated one. 
The tests should pass, also the tolerance threshold for the error is quite high (1e-2). Note that some solvers are also more or less precise, and may require a smaller step size.

To run the tests, you can execute either run the tests from your IDE, or write the following commands from the build folder:
```
./tests
```
It should output the tests status on the terminal (starting with `Running 14 tests from 4 test suites`).

## Limitations

We encountered various challenges during the realisation of this project, some were taken care of, and some remain as limitations of our implementation.

### Solvers classes
Our first main challenge was to find a suitable class organisation for the different solvers. 

A good knowledge of the methods was needed to understand how they relate with each other, and what were their common and specific characteristics.
There are different approaches we thought about, and we decided to split the methods between two main categories: **explicit** and **implicit**.
The explicit methods can be single-step or multi-step methods. 

Another approach we thought about was to separate in two other categories: Runge-Kutta and linear multi-step methods.
Then linear multi-step methods could have been split between explicit and implicit and would have been determined by their weights.

### Function classes
Our second main challenge was to create a function class, and handle the derivatives.
We decided to create a base class (`ODERighHandSide`) and two child classes that correspond to functions for which we know the derivative and for which we do not.
If the derivative is unknown, it is approximated using centered differences.

There are however a few limitations with our approach.
- We only provided 2 types of built-in functions: `ModelProblemRHS` and `PolynomialRHS`.
- Despite the possibility of using arbitrary functions in `UserDefinedRHS`, we didn't manage to implement it in a way that allows the user to avoid recompilation.
  Additionally, the user needs to specify whether they want to use a known or unknown derivative for the function.


### Dimension of the ODE
The main limitation of our project is that it focuses strictly on ordinary differential equations (ODEs) that map from $\mathbb{R} \times \mathbb{R}$ to $\mathbb{R}$.
In other words, both $y$ and $t$ are real numbers, and the function $f$, defined by $f: \mathbb{R} \times \mathbb{R} \to \mathbb{R}$, is also real-valued.
Possible extensions could include:
- Allowing $y$ to be a vector,  i.e. $y \in \mathbb{R}^n$,
- Enabling $\mathbf{f}$ to be a vector-valued function, allowing it to solve systems of ODEs by defining $\mathbf{f}: \mathbb{R} \times \mathbb{R}^n \to \mathbb{R}^n$,
- Extending $y$ to be a complex number or a complex-valued vector, altering the domain and range of $f$ to include complex dimensions.

To implement these extensions, we are considering the use of template classes and/or Eigen vectors for variable types of $y$.
