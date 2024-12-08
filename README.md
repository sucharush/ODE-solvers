# Project: *Programming concepts in scientific computing* (MATH-458, EPFL, 2024).

## Table of contents
- [Description of the project](#decription-of-the-project)
- [How to](#how-to)
- [Features](#features)
- [Limitations](#limitations)

## Description of the project
This project focuses on ODE, with generic non-linear function, i.e. $y^{'}(t)=f(t,y(t))$.

We are interested in developping different methods to solve this problem.

## How to
### Quick Start
```
git clone git@gitlab.epfl.ch:ebaup/pcsc-project.git
cd pcsc-project
```
### Set-up
In order to compile it you should first install *googletest* and *eigen*

```
git submodule update --init 
```

Then, you can build the project as usual, e.g. with CLion or in the terminal by writing the following commands:

```
mkdir build
cd build
cmake ..
make
```
After these lines, executable files are produced. To execute the main file, 
you can either run 'main' on your IDE, 
or run the following lines on your terminal:

```
cd .. // or simply open your terminal in the root project folder
./main
```
Instructions should appear to guide you. 

TODO complete instructions if needed, typical execution

## Features

## Limitations