#!/usr/bin/env python
# -*- coding: utf-8 -*-
#==============================================================================
# Title:           FYS3150 Project 3a
# Author:          Erik Johannes B. L. G. Husom
# Date:            2018-00-00
# Version:         0.1
# Python version:  Python 3.6.4
# Description:
# USAGE:
#==============================================================================
# IMPORT STATEMENTS
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
# SET PLOT STYLE
plt.style.use('ggplot')
plt.rcParams.update({'font.size': 15})
plt.rc("text", usetex=True)
w = 15; h = 10

# LOAD DATA
ObjectPositions = np.loadtxt('SolarSystem.dat')
objectNames = np.array(['Sun', 'Mercury', 'Venus', 'Earth', 'Mars', 'Jupiter', 'Saturn', 'Uranus', 'Neptune', 'Pluto'])

# PLOT
fig = plt.figure(figsize=(w,h))
ax = fig.gca(projection='3d')
ax.set_aspect('equal')

for i in range(np.size(objectNames)):
    plt.plot(ObjectPositions[:,i*3], ObjectPositions[:,i*3+1], ObjectPositions[:,i*3+2], label=objectNames[i])

plt.title('Position of planets')
plt.xlabel('x axis [AU]')
plt.ylabel('y axis [AU]')
ax.set_zlabel('z axis [AU]')
plt.legend()
plt.tight_layout()
plt.savefig("solarsystem.pdf",dpi=300)
plt.show()
