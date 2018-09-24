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
plt.rc('text', usetex=True)
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
# mesh points
n = np.array([10,20,30,40,50,100,150,200,300,400])
time_J = np.zeros(np.size(n))
std_J = np.zeros(np.size(n))
time_A = np.zeros(np.size(n))
std_A = np.zeros(np.size(n))
for i in range(np.size(n)):
    data = np.loadtxt('timingsn{:d}.dat'.format(n[i]))
    J, A = data[:,0], data[:,1]
    time_J[i] = np.mean(J)
    std_J[i] = np.std(J)
    time_A[i] = np.mean(A)
    std_A[i] = np.std(A)

# iterations of Jacobi method
it = np.array([154, 640, 1488, 2657, 4112, 16401, 36570, 64509, 143659, 252793])
plt.figure(figsize=(w,h))
plt.plot(n,time_J, '-', label="Jacobi")
plt.plot(n,time_A, '-', label="Armadillo")
plt.xlabel("No. of mesh points $n$")
plt.ylabel("Run time $[s]$")
plt.legend()
plt.tight_layout()
plt.savefig("runtime.pdf",dpi=300)
    plt.show()
