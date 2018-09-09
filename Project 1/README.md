# Project 1 - Numerically solving the one-dimensional Poisson's Equation
This project contains the following files:
- `project1.cpp`: Main program, which computes the numerical solution of the differential equation with three different algorithms for different step lengths, in addition to the relative error, and writes all the data to files.
- `dataplot.py`: Reads data from the above program and plots all the numerical solutions against the analytical solution.
- `dataplot_eps.py`: Reads data written by the main program about the relative error and plots it on a log/log-scale versus the step length.
- `timings.py`: Calculates the average run time for the algorithms, which are timed by the main program, and writes the result to the benchmark-file.
- `benchmark.md`: Contains the average run time for the algorithms as written by `timings.py`.
All source code in this project is developed for Ubuntu 18.04 with C++ and Python 3.6.
