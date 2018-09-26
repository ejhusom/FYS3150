#!/usr/bin/env python
# -*- coding: utf-8 -*-
#==============================================================================
# Title:            Plot results in project 2
# Author:           Erik Johannes B. L. G. Husom
# Date:             2018-09-24
# Version:          3.0
# Python version:   Python 3.6.4
# Description: Plotting data from .dat-files, specialized for FYS3150 project 2
# USAGE:
# Requires various data files, which may be produced by main.cpp.
# Uncomment the parts which you want to plot.
#==============================================================================
# IMPORT STATEMENTS
import numpy as np
import matplotlib.pyplot as plt
# SET PLOT STYLE
plt.style.use('ggplot')
plt.rcParams.update({'font.size': 8})
plt.rcParams['text.latex.preamble'] = [r'\usepackage{amsmath}']
plt.rc('text', usetex=True)
plt.rc('font', **{'family': 'serif', 'serif': ['Computer Modern']})
w = 5; h = 2.5
#==============================================================================
# PLOT THE WAVE FUNCTION
# plt.figure(figsize=(w,h))
# omega = np.array([0.01,0.5,1.0,5.0])
# for i in range(4):
#     rho = np.loadtxt('rho_o{:.6f}.dat'.format(omega[i]))
#     eigvec = np.loadtxt('eigvec_o{:.6f}.dat'.format(omega[i]))
#     vec1 = eigvec[:,0]
#     plt.plot(rho,vec1**2,label='$\omega_r={:g}$'.format(omega[i]))
# plt.xlabel(r'$\rho$')
# plt.ylabel(r'Radial probability $|R(\rho)|^2$')
# plt.legend()
# plt.tight_layout()
# plt.savefig("wavefunction.pdf",dpi=400)
# plt.show()
#==============================================================================
# PLOT RUN TIME AND ITERATIONS
# mesh points
# n = np.array([10,20,30,40,50,100,150,200,300,400])
# time_J = np.zeros(np.size(n))
# std_J = np.zeros(np.size(n))
# time_A = np.zeros(np.size(n))
# std_A = np.zeros(np.size(n))
# for i in range(np.size(n)):
#     data = np.loadtxt('timingsn{:d}.dat'.format(n[i]))
#     J, A = data[:,0], data[:,1]
#     time_J[i] = np.mean(J)
#     std_J[i] = np.std(J)
#     time_A[i] = np.mean(A)
#     std_A[i] = np.std(A)
#
# plt.figure(figsize=(w,h))
# plt.plot(n,time_J, '-o', label="Jacobi")
# plt.plot(n,time_A, '-', label="Armadillo")
# plt.xlabel("No. of mesh points $n$")
# plt.ylabel("No. of iterations")
# plt.legend()
# plt.tight_layout()
# plt.savefig("runtime.pdf",dpi=300)
# # plt.show()
#
# iterations of Jacobi method
# it = np.array([154, 4112, 16401, 36570, 64509, 143659, 252793])
# n = np.array([10,50,100,150,200,300,400])
# deg,res,v1,v2,v3 = np.polyfit(n,it,5,full=True);
# p = np.poly1d(deg);
# xp = np.linspace(10,400,400)
# plt.figure(figsize=(w,h))
# plt.plot(n,it, 'o',label="recorded number of iterations")
# plt.plot(xp,p(xp),label="least squares fit of second degree")
# plt.xlabel("$\\text{No. of mesh points} \hspace{0.2cm} n$")
# plt.ylabel("$\\text{No. of iterations}$")
# plt.legend()
# plt.tight_layout()
# plt.savefig("iterations.pdf",dpi=400)
# plt.show()
#
# # Save mean and std of run times to .csv-file
# n = np.array([10,20,30,40,50,100,150,200,300,400])
# a = np.zeros((10,5))
# a[:,0], a[:,1], a[:,2], a[:,3], a[:,4] = n, time_J, std_J, time_A, std_A
# np.savetxt("runtime.csv", a, delimiter=' & ', fmt='%2.6f', newline=' \\\\\n')
#==============================================================================
# # PLOT EIGENVALUES - ONE ELECTRON
# data = np.loadtxt('accuracy_rho_n150.dat')
# lambda1, lambda2, lambda3, lambda4 = data[:,0], data[:,1], data[:,2], data[:,3]
# rho_max = np.linspace(3,7,41)
# plt.figure(figsize=(w,h))
# plt.plot(rho_max,lambda1,label="$\lambda_1$")
# plt.plot(rho_max,lambda2,label="$\lambda_2$")
# plt.plot(rho_max,lambda3,label="$\lambda_3$")
# plt.plot(rho_max,lambda4,label="$\lambda_4$")
# plt.xlabel("$\\rho_{\mathrm{max}}$")
# plt.ylabel("$\\text{Ratio} \hspace{0.3cm}\lambda_\mathrm{c}/\lambda_\mathrm{a}$")
# plt.axis([3,6,0.998, 1.002])
# plt.tight_layout()
# plt.legend()
# plt.savefig("accuracy_rho_n150.pdf",dpi=400)
# # plt.show()
# data = np.loadtxt('accuracy_rho_n200.dat')
# lambda0, lambda1, lambda2, lambda3 = data[:,0], data[:,1], data[:,2], data[:,3]
# rho_max = np.linspace(3,6,31)
# plt.figure(figsize=(w,h))
# plt.plot(rho_max,lambda0,label="$\lambda_0$")
# plt.plot(rho_max,lambda1,label="$\lambda_1$")
# plt.plot(rho_max,lambda2,label="$\lambda_2$")
# plt.plot(rho_max,lambda3,label="$\lambda_3$")
# plt.xlabel("$\\rho_{\mathrm{max}}$")
# plt.ylabel("$\\text{Ratio} \hspace{0.3cm}\lambda_\mathrm{c}/\lambda_\mathrm{a}$")
# plt.axis([3,6,0.999, 1.002])
# plt.tight_layout()
# plt.legend()
# plt.savefig("accuracy_rho_n200.pdf",dpi=400)
# # plt.show()
# data = np.loadtxt('accuracy_n_rho5_v2.dat')
# lambda0, lambda1, lambda2, lambda3 = data[:,0], data[:,1], data[:,2], data[:,3]
# n = np.linspace(10,400,40)
# plt.figure(figsize=(w,h))
# plt.plot(n,lambda0,label="$\lambda_0$")
# plt.plot(n,lambda1,label="$\lambda_1$")
# plt.plot(n,lambda2,label="$\lambda_2$")
# plt.plot(n,lambda3,label="$\lambda_3$")
# plt.xlabel("$\\text{No. of mesh points} \hspace{0.2cm} n$")
# plt.ylabel("$\\text{Ratio} \hspace{0.3cm}\lambda_\mathrm{c}/\lambda_\mathrm{a}$")
# plt.axis([100,400,0.999, 1.001])
# plt.tight_layout()
# plt.legend()
# plt.savefig("accuracy_n_rho5.pdf",dpi=400)
# plt.show()
