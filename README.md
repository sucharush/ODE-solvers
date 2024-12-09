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

## Project Overview
This project provides an implementation of numerical solvers for solving ordinary differential equations (ODEs), 
i.e. $y^{'}(t)=f(t,y(t)).$. The solvers currently support the following methods:

- **Forward Euler (FE)**: Explicit single-step solver.
- **Runge-Kutta (RK)**: Explicit single-step solver supporting orders 1 through 4.
- **Adams-Bashforth (AB)**: Explict multistep solver with configurable order and initialization method (e.g., RK4, Forward Euler).
- **Backward Euler (BE)**: Implicit single-step solver with optional tolerance and iteration settings.

The default implementation solves the model problem $y^{'} = -0.3y$ using a 4th-order Runge-Kutta method. 
The project is modular, allowing customization of solvers, models, and configurations.

The main structure of the project is as follows:
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
    │   ├── EXplicitSolver.h                          // Base class for all explicit solvers
    │   ├── ForwardEulerSolver.h                    
    │   ├── ImplicitSolver.h                          // Base class for implicit solvers
    │   ├── json.hpp                      
    │   ├── KnownDerivativeRHS.h                      // RHS with analytically known derivative
    │   ├── ODERightHandSide.h                        // Base class for RHS functions
    │   ├── RungeKuttaSolver.h                       
    │   ├── SolverFactory.h                           
    │   └── UnknownDerivativeRHS.h                    // RHS with unknown derivative 
    ├── src/
    │   └── [Corresponding .cc files implementing the headers]
    ├── test/
    ├── .gitignore
    ├── .gitmodules
    ├── main.cc                                     
    └── CMakeLists.txt                               


```
## How to
### Quick Start
```
git clone git@gitlab.epfl.ch:ebaup/pcsc-project.git
cd pcsc-project
```
### Set-up and Building
The project relies on *googletest* and *Eigen*, initialize submodules to install these dependencies:

```
git submodule update --init 
```

You can build the project using your preferred IDE (e.g., CLion) or the terminal:
```
mkdir build
cd build
cmake ..
make
```
After these lines, executable files are produced. Simply run 'main' on your IDE, 
or run the following lines on your terminal:

```
cd .. // or simply open your terminal in the root project folder
./main
```
[//]: # (Instructions should appear to guide you. )
[//]: # (TODO complete instructions if needed, typical execution)
###  Update the Configuration
Modify the `config/config.json` file to set global parameters and solver-specific options. 
```
{
  "global": {
    "stepSize": The time step for the solver,
    "t0": Start time of the simulation,
    "t1": End time of the simulation,
    "initialValue": Initial guess y_0,
  },
  "solver": {
    "method": Solver type, choosing from {"RK", "AB", "BE", "FE"},
    "parameters": {
      "order": For Runge Kutta, choosing from {1, 2, 4}, 
      "steps": For AdamsBashforth, choosing from {1, 2, 3, 4}, 
      "initMethod": For AdamsBashforth, choosing from {"RK4", "FE"},
      "tolerance": For Newton method in backward Euler, defaulted as 1e-6,
      "maxIter": For Newton method in backward Euler, defaulted as 50
    }
  }
}
```
**Note:** It will automatically build Forward Euler solver when choosing `order = 1` for Runge Kutta
or `steps = 1` for AdamsBashforth.
### Modify the RHS Function

[//]: # (TODO logic)


## Limitations