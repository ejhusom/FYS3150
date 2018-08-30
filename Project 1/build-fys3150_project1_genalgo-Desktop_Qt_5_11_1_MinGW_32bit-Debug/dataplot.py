#!/usr/bin/env python
# -*- coding: utf-8 -*-
#==============================================================================
# Title:            Data Plot
# Author:           Erik Johannes B. L. G. Husom
# Date:             2018-08-24
# Version:          0.1
# Python version:   Python 3.6.4
# Description:      Plotting data from .dat-files
#==============================================================================
# IMPORT STATEMENTS
import numpy as np
import matplotlib.pyplot as plt

def readFile(filename):
    infile = open(filename, "r")
    x = []
    num = []
    anal = []
    for line in infile:
        a = line.split()
        x.append(float(a[0]))
        num.append(float(a[1]))
        anal.append(float(a[2]))
    return x, num, anal


fileData = readFile("specalgo.dat")

plt.plot(fileData[0], fileData[1], 'ro', label='num')
plt.plot(fileData[0], fileData[2], label='anal')
plt.legend()
plt.show()
