# Project 3 - The Solar System

All source-files in this project is located in the ```src``` folder, and all header files in the ```include``` folder.

- Class ```AstronomicalObject``` represents the objects that are a part of the simulation (i.e. the Sun, planets etc.).
- Class ```Integrator``` is used to simulate the movement of the objects in the solar system. It is possible to choose both the Velocity Verlet method and the Euler method, though the latter is not stable for this problem.
- ```plotSolarSystem.py``` is used to generate a 3D-plot of the solar system.
- ```TwoBodyProblem.cpp``` is a simpler program, only simulating the Earth's rotation around a static Sun.

Generate an executable by running ```make``` in the terminal.

All source code in this project is developed for Ubuntu 18.04 with C++ and Python 3.6.
