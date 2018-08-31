#!/usr/bin/env python
# -*- coding: utf-8 -*-
#==============================================================================
# Title:            Data Plot
# Author:           Erik Johannes B. L. G. Husom
# Date:             2018-08-24
# Version:          1.0
# Python version:   Python 3.6.4
# Description:      Plotting data from .dat-files, specialized for FYS3150
#                   project 1
#==============================================================================
# IMPORT STATEMENTS
import numpy as np
import matplotlib.pyplot as plt

def readFile(filename):
    infile = open(filename, "r")
    x = []
    num = []
    anal = []
    eps = []
    for line in infile:
        a = line.split()
        x.append(float(a[0]))
        num.append(float(a[1]))
        anal.append(float(a[2]))
        eps.append(float(a[3]))
    return x, num, anal, eps



fileData = readFile("specalgo.dat")

x,v,u,eps = fileData

x = np.array(x)
v = np.array(v)
u = np.array(u)
eps = np.array(eps)

# Python calculation of relative errors
e = np.log10(abs((v-u)/u))

# plt.plot(fileData[0], fileData[1], label='num', LineWidth=4)
# plt.plot(fileData[0], fileData[2], label='anal')
# plt.legend()
# plt.show()
plt.plot(x[1:-1], e[1:-1], label='python')
plt.plot(fileData[0][1:-1], fileData[3][1:-1], label='c++')
plt.legend()
plt.show()
