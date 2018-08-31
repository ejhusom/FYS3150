#!/usr/bin/env python
# -*- coding: utf-8 -*-
#==============================================================================
# Title:            Data Plot of Error
# Author:           Erik Johannes B. L. G. Husom
# Date:             2018-08-24
# Version:          0.1
# Python version:   Python 3.6.4
# Description:      Plotting data from error-file in FYS3150
#                   project 1
#==============================================================================
# IMPORT STATEMENTS
import numpy as np
import matplotlib.pyplot as plt

def readFile(filename):
    infile = open(filename, "r")
    log10h = []
    eps = []
    for line in infile:
        a = line.split()
        log10h.append(float(a[0]))
        eps.append(float(a[1]))
    return log10h, eps



data = readFile("epsilons.dat")

plt.plot(data[0], data[1], 'ro-')
plt.legend()
plt.show()
