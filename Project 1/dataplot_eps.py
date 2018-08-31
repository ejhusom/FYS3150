#!/usr/bin/env python
# -*- coding: utf-8 -*-
#==============================================================================
# Title:            Data Plot of Error
# Author:           Erik Johannes B. L. G. Husom
# Date:             2018-08-24
# Version:          2.0
# Python version:   Python 3.6.4
# Description: Plotting data from error-file in FYS3150 project 1
#==============================================================================
# IMPORT STATEMENTS
import numpy as np
import matplotlib.pyplot as plt

# LOAD DATA
data = np.loadtxt('epsilons.dat')
log10h = data[:,0]
eps = data[:,1]

# PLOT EPSILON VS H on a log-scale
plt.plot(log10h,eps, 'b-o')
plt.xlabel('$log_{10}(h)$')
plt.ylabel('$log_{10}(\epsilon)$')
plt.legend()
plt.show()
