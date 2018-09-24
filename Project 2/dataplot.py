#!/usr/bin/env python
# -*- coding: utf-8 -*-
#==============================================================================
# Title:            Plot results in project 2
# Author:           Erik Johannes B. L. G. Husom
# Date:             2018-09-24
# Version:          3.0
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
# # PLOT PSI
# plt.figure(figsize=(w,h))
# rho = np.loadtxt('rho.dat')
# eigvec = np.loadtxt('eigvec.dat')
# vec1, vec2, vec3 = eigvec[:,0],eigvec[:,1],eigvec[:,2]
# plt.plot(rho,vec1**2)
# plt.plot(rho,vec2**2)
# plt.plot(rho,vec3**2)
# plt.xlabel(r'$r$')
# plt.ylabel(r'Radial probability $r^2|R(r)|^2$')
# plt.tight_layout()
# # plt.savefig("eigenvectors.png",dpi=300)
# plt.show()
#==============================================================================
# PLOT RUN TIME AND ITERATIONS
data = np.loadtxt('timings.dat')
J, A= data[:,0], data[:,1]
print(np.mean(J))
print(np.mean(A))


plt.figure(figsize=(w,h))
# mesh points
n = np.array([10,20,30,40,50,100,150,200,250,300,400])
# run time Jacobi, averaged over 10 runs
tJ = np.array([0.0001667618, 0.0001747896, 0.006797954, 0.0167857766, 0.036632349, 0.3405486715,1.5824691189, 0, 0, 0, 0])
# run time Armadillo, averaged over 10 runs
tA = np.array([0.0001747896, 0.0003280219, 0.0004675504, 0.0015659237, 0.0012658448, 0.0028739736, 0.0045126838, 0, 0, 0, 0])
# iterations of Jacobi method
it = np.array([154, 640, 1488, 2657, 4112, 16401, 36570, 64509, 100077, 143659, 252793])
plt.plot(n,tJ, '-*', label="Jacobi")
plt.plot(n,tA, '-*', label="Armadillo")
plt.xlabel("No. of mesh points $n$")
plt.ylabel("Run time $[s]$")
plt.legend()
plt.tight_layout()
plt.savefig("runtime.pdf",dpi=300)
plt.show()
