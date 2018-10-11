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
classtest = np.loadtxt('ClassData33.dat')
xPosS,yPosS,zPosS,xPosE,yPosE,zPosE,xPosJ,yPosJ,zPosJ = classtest[:,0], classtest[:,1], classtest[:,2], classtest[:,3], classtest[:,4], classtest[:,5],classtest[:,6],classtest[:,7],classtest[:,8]
# POSITION
fig = plt.figure(figsize=(w,h))
ax = fig.gca(projection='3d')
ax.set_aspect('equal')
plt.plot(xPosS,yPosS,zPosS,label='Sun')
plt.plot(xPosE,yPosE,zPosE,label='Earth')
plt.plot(xPosJ,yPosJ,zPosJ,label='Jupiter')
plt.title('Earth Position')
plt.xlabel('x axis [AU]')
plt.ylabel('y axis [AU]')
plt.legend()
plt.tight_layout()
# plt.savefig("title.pdf",dpi=300)
plt.show()
