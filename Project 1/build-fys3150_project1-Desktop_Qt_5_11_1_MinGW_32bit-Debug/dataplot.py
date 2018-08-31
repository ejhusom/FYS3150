#!/usr/bin/env python
# -*- coding: utf-8 -*-
#==============================================================================
# Title:            Data Plot
# Author:           Erik Johannes B. L. G. Husom
# Date:             2018-08-24
# Version:          2.0
# Python version:   Python 3.6.4
# Description: Plotting data from .dat-files, specialized for FYS3150 project 1
#==============================================================================
# IMPORT STATEMENTS
import numpy as np
import matplotlib.pyplot as plt

# LOAD DATA
data = np.loadtxt('specalgo.dat')
x, u, v, eps = data[:,0], data[:,1], data[:,2], data[:,3]

# PLOT NUMERICAL VS ANALYTICAL
plt.plot(x,v,label='numerical',LineWidth=3.0)
plt.plot(x,u,label='analytical')
plt.legend()
plt.show()
# PLOT ERROR
plt.plot(x[1:-1],eps[1:-1])
plt.legend()
plt.show()
