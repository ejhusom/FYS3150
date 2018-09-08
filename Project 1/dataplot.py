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
# SET PLOT STYLE
plt.style.use('ggplot')
#==============================================================================
# PLOT GENERAL ALGORITHM
data = np.loadtxt('genalgo1000.dat')
x, u, v, eps = data[:,0], data[:,1], data[:,2], data[:,3]
plt.plot(x,u,label='analytical')
for i in range(3):
    data = np.loadtxt('genalgo{:d}.dat'.format(int(10**(i+1))))
    x, u, v, eps = data[:,0], data[:,1], data[:,2], data[:,3]
    plt.plot(x,v,'--',label='n={:d}'.format(int(10**(i+1))))
plt.xlabel('$x$')
plt.ylabel('$u$')
plt.legend()
plt.show()
#==============================================================================
# PLOT SPECIALIZED ALGORITHM
data = np.loadtxt('specalgo1000.dat')
x, u, v, eps = data[:,0], data[:,1], data[:,2], data[:,3]
plt.plot(x,u,label='analytical')
for i in range(6):
    data = np.loadtxt('specalgo{:d}.dat'.format(int(10**(i+1))))
    x, u, v, eps = data[:,0], data[:,1], data[:,2], data[:,3]
    plt.plot(x,v,'--',label='n={:d}'.format(int(10**(i+1))))
plt.xlabel('$x$')
plt.ylabel('$u$')
plt.legend()
plt.show()
#==============================================================================
# PLOT LU ALGORITHM
# data = np.loadtxt('lud.dat')
# lux, luf = data[:,0], data[:,1]
# plt.plot(lux,luf,label='LU-decomposition')
