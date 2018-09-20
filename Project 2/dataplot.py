#!/usr/bin/env python
# -*- coding: utf-8 -*-
#==============================================================================
# Title:            Data Plot
# Author:           Erik Johannes B. L. G. Husom
# Date:             2018-08-24
# Version:          2.0
# Python version:   Python 3.6.4
# Description: Plotting data from .dat-files, specialized for FYS3150 project 2
#==============================================================================
# IMPORT STATEMENTS
import numpy as np
import matplotlib.pyplot as plt
# SET PLOT STYLE
plt.style.use('ggplot')
plt.rcParams.update({'font.size': 8})
w = 5; h = 2.5
#==============================================================================
# PLOT GENERAL ALGORITHM
plt.figure(figsize=(w,h))
data = np.loadtxt('eigenvectors.dat')
x = data[:,1]
plt.plot(x)
plt.xlabel('$x$')
plt.ylabel('$u$')
plt.legend()
plt.tight_layout()
# plt.savefig("eigenvectors.png",dpi=300)
plt.show()
