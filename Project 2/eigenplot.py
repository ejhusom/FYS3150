#!/usr/bin/env python
# -*- coding: utf-8 -*-
#==============================================================================
# Title:            Plot Eigenvectors
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
rho = np.loadtxt('rho.dat')
eigvec = np.loadtxt('eigvec.dat')
vec1, vec2, vec3 = eigvec[:,0],eigvec[:,1],eigvec[:,2]
plt.plot(rho,vec1**2)
plt.plot(rho,vec2**2)
plt.plot(rho,vec3**2)
# plt.axis([0,4.6,0.0, 0.025])
plt.xlabel(r'$r$')
plt.ylabel(r'Radial probability $r^2|R(r)|^2$')
plt.tight_layout()
# plt.savefig("eigenvectors.png",dpi=300)
plt.show()
