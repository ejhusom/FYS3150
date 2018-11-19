#!/usr/bin/env python
# -*- coding: utf-8 -*-
#==========================================================================
# Program by Erik Johannes B. L. G. Husom on 2018-11-01 for Python 3.6.4
# Description: Run and plot project 4 in FYS3150
# USAGE:
#==========================================================================
# IMPORT STATEMENTS
import numpy as np
import sys, os
import matplotlib.pyplot as plt
import matplotlib.mlab as mlab
from scipy.stats import norm
# SET PLOT STYLE
plt.style.use('ggplot')
plt.rcParams.update({'font.size': 8})
plt.rc("text", usetex=True)
plt.rc('font', family='serif')
w = 5; h = 2.5

# USER INPUT
rows, columns = os.popen('stty size', 'r').read().split()
for i in range(int(columns)):
    print('=',end='')
print("FYS3150 Project 4 - Ising Model")
task = input('Which task (b, c1, c2, c3, d, e, f)=')
print('Run simulation and produce data files? Enter \'n\' to move on to plotting.')
run = input('y/n=')
if (task=='b'):
    if (run=='y'):
        dim = 2
        state = 1
        nCycles = 1000000
        temp_init = 1.0
        temp_final = 1.1
        temp_step = 1.0
        os.system('make')
        print('Running project for task ' + task + '...')
        os.system('mpirun -n 4 ./runproject4.x ' + str(dim) + ' ' + str(state) + ' ' + str(nCycles) + ' ' + str(temp_init) + ' ' + str(temp_final) + ' ' + str(temp_step))
if (task=='c1'):
    # The two following lines are needed in metropolis.cpp to produce data
    # cout << setw(15) << setprecision(8) << *E/100/dim/dim;
    # cout << setw(15) << setprecision(8) << fabs(*M)/100/dim/dim << endl;
    dim = 20
    states = [0]
    nCycles = 100
    temp_init = 1.0
    temp_final = 2.4
    temp_step = 1.4
    if (run=="y" ):
        os.system('make')
        print('Running project for task ' + task + '...')
        for state in states:
            os.system('mpirun -n 1 ./runproject4.x ' + str(dim) + ' ' + str(state) + ' ' + str(nCycles) + ' ' + str(temp_init) + ' ' + str(temp_final) + ' ' + str(temp_step))
    rand1 = np.loadtxt("4cState0T1.dat")
    rand24 = np.loadtxt("4cState0T24.dat")
    ord1 = np.loadtxt("4cState1T1.dat")
    ord24 = np.loadtxt("4cState1T24.dat")
    plt.figure(figsize=(w,h))
    plt.plot(rand1[:,0],label='Random lattice')
    plt.plot(ord1[:,0],label='Ordered lattice')
    plt.xlabel('No. of Monte Carlo cycles')
    plt.ylabel(r'Energy')
    plt.legend()
    plt.tight_layout()
    plt.savefig("/home/ejhusom/MEGAsync/FAM/FYS3150/project4/report_project4/taskc_E1.pdf",dpi=300)
    plt.show()
    plt.figure(figsize=(w,h))
    plt.plot(rand1[:,1],label='Random lattice')
    plt.plot(ord1[:,1],label='Ordered lattice')
    plt.xlabel('No. of Monte Carlo cycles')
    plt.ylabel(r'Magnetization')
    plt.legend()
    plt.tight_layout()
    plt.savefig("/home/ejhusom/MEGAsync/FAM/FYS3150/project4/report_project4/taskc_M1.pdf",dpi=300)
    plt.show()
    plt.figure(figsize=(w,h))
    plt.plot(rand24[:,0],label='Random lattice')
    plt.plot(ord24[:,0],label='Ordered lattice')
    plt.xlabel('No. of Monte Carlo cycles')
    plt.ylabel(r'Energy')
    plt.legend()
    plt.tight_layout()
    plt.savefig("/home/ejhusom/MEGAsync/FAM/FYS3150/project4/report_project4/taskc_E24.pdf",dpi=300)
    plt.show()
    plt.figure(figsize=(w,h))
    plt.plot(rand24[:,1],label='Random lattice')
    plt.plot(ord24[:,1],label='Ordered lattice')
    plt.xlabel('No. of Monte Carlo cycles')
    plt.ylabel(r'Magnetization')
    plt.legend()
    plt.tight_layout()
    plt.savefig("/home/ejhusom/MEGAsync/FAM/FYS3150/project4/report_project4/taskc_M24.pdf",dpi=300)
    plt.show()
if (task=='c2'):
    dim = 20
    states = [0,1]
    nCycles = [100,1000,10000,100000,1000000]
    temp_init = 1.0
    temp_final = 1.1
    temp_step = 1.0
    if (run=="y" ):
        os.system('make')
        print('Running project for task ' + task + '...')
        for state in states:
            for N in nCycles:
                os.system('mpirun -n 4 ./runproject4.x ' + str(dim) + ' ' + str(state) + ' ' + str(N) + ' ' + str(temp_init) + ' ' + str(temp_final) + ' ' + str(temp_step))
    rand_accepts1 = []
    ord_accepts1 = []
    for N in nCycles:
        data = np.loadtxt("Dim" + str(dim) + "State" + '0' + "Cycles" + str(N) + "T" + str(temp_init) + "00000.dat", skiprows=1)
        rand_accepts1.append(data[9])
    for N in nCycles:
        data = np.loadtxt("Dim" + str(dim) + "State" + '1' + "Cycles" + str(N) + "T" + str(temp_init) + "00000.dat", skiprows=1)
        ord_accepts1.append(data[9])
    plt.figure(figsize=(w,h))
    plt.semilogx(nCycles,ord_accepts1,'x-',label='Ordered lattice')
    plt.semilogx(nCycles,rand_accepts1,'x-',label='Random lattice')
    plt.xlabel('No. of Monte Carlo cycles')
    plt.ylabel('No. of accepted config.')
    plt.legend()
    plt.tight_layout()
    plt.savefig("/home/ejhusom/MEGAsync/FAM/FYS3150/project4/report_project4/taskc_accepts.pdf",dpi=300)
    plt.show()
if (task=='c3'):
    dim = 20
    states = [0,1]
    nCycles = 100000
    temp_init = 1.0
    temp_final = 5.0
    temp_step = 0.1
    if (run=="y" ):
        os.system('make')
        print('Running project for task ' + task + '...')
        for state in states:
            os.system('mpirun -n 4 ./runproject4.x ' + str(dim) + ' ' + str(state) + ' ' + str(nCycles) + ' ' + str(temp_init) + ' ' + str(temp_final) + ' ' + str(temp_step))
    rand_data = np.loadtxt("Dim" + str(dim) + "State" + '0' + "Cycles" + str(nCycles) + "T" + str(temp_init) + "00000.dat", skiprows=1)
    ord_data = np.loadtxt("Dim" + str(dim) + "State" + '1' + "Cycles" + str(nCycles) + "T" + str(temp_init) + "00000.dat", skiprows=1)
    plt.figure(figsize=(w,h))
    plt.plot(ord_data[:,0],ord_data[:,9],label='Ordered lattice')
    plt.plot(rand_data[:,0],rand_data[:,9],'-.',label='Random lattice')
    plt.xlabel('Temperature [kJ/T]')
    plt.ylabel('No. of accepted config.')
    plt.legend()
    plt.tight_layout()
    plt.savefig("/home/ejhusom/MEGAsync/FAM/FYS3150/project4/report_project4/taskc_accepts_temp.pdf",dpi=300)
    plt.show()
if (task=='d'):
    dim = 20
    states = [1]
    nCycles = 1000000
    temp_init = 1.0
    temp_final = 2.4
    temp_step = 1.4
    if (run=="y" ):
        os.system('make')
        print('Running project for task ' + task + '...')
        for state in states:
            os.system('mpirun -n 1 ./runproject4.x ' + str(dim) + ' ' + str(state) + ' ' + str(nCycles) + ' ' + str(temp_init) + ' ' + str(temp_final) + ' ' + str(temp_step))
    E1 = np.loadtxt("4dState1T1.000000.dat")
    E24 = np.loadtxt("4dState1T2.400000.dat")
    indices = int(round(len(E1)*0.9))
    Earrays = [E1,E24]
    filename = 1
    for E in Earrays:
        plt.figure(figsize=(w,h))
        E = E[indices:]
        a = np.min(E)
        b = np.max(E)
        x = np.linspace(a,b,1000)
        num_bins = 50
        mu, sigma = norm.fit(E)
        n, bins, patches = plt.hist(E, num_bins, density=True, align='mid', alpha=0.75)
        y = mlab.normpdf(bins, mu, sigma)
        plt.plot(bins, y)
        plt.xlabel("Energy")
        plt.ylabel("Probability density")
        if (filename == 1):
            plt.locator_params(nbins=4)
        plt.legend(["Normal distribution", "Sampled energy"])
        plt.tight_layout()
        plt.savefig("/home/ejhusom/MEGAsync/FAM/FYS3150/project4/report_project4/taskd_" + str(filename) + ".pdf",dpi=300)
        plt.show()
        filename += 23
if (task=='e'):
    dim = [40,60,80,100,120]
    state = 1
    nCycles = 100000
    temp_init = 2.24
    temp_final = 2.32
    temp_step = 0.01
    if (run=="y" ):
        os.system('make')
        print('Running project for task ' + task + '...')
        for d in dim:
            os.system('mpirun -n 4 ./runproject4.x ' + str(d) + ' ' + str(state) + ' ' + str(nCycles) + ' ' + str(temp_init) + ' ' + str(temp_final) + ' ' + str(temp_step))
    data40 = np.loadtxt("Dim40State1Cycles100000T2.240000.dat", skiprows=1)
    data60 = np.loadtxt("Dim60State1Cycles100000T2.240000.dat", skiprows=1)
    data80 = np.loadtxt("Dim80State1Cycles100000T2.240000.dat", skiprows=1)
    data100 = np.loadtxt("Dim100State1Cycles100000T2.240000.dat", skiprows=1)
    data120 = np.loadtxt("Dim120State1Cycles100000T2.240000.dat", skiprows=1)
    # data40 = np.loadtxt("Dim40State1Cycles100000T2.000000.dat", skiprows=1)
    # data60 = np.loadtxt("Dim60State1Cycles100000T2.000000.dat", skiprows=1)
    # data80 = np.loadtxt("Dim80State1Cycles100000T2.000000.dat", skiprows=1)
    # data100 = np.loadtxt("Dim100State1Cycles1000000T2.000000.dat", skiprows=1)

    plt.figure(figsize=(w,h))
    plt.plot(data40[:,0],data40[:,1],'x-',label='L=40')
    plt.plot(data40[:,0],data60[:,1],'x-',label='L=60')
    plt.plot(data40[:,0],data80[:,1],'x-',label='L=80')
    plt.plot(data40[:,0],data100[:,1],'x-',label='L=100')
    plt.plot(data40[:,0],data120[:,1],'x-',label='L=120')
    plt.xlabel('Temperature [kJ/T]')
    plt.ylabel(r'$\langle E \rangle$')
    plt.legend()
    plt.tight_layout()
    plt.savefig("/home/ejhusom/MEGAsync/FAM/FYS3150/project4/report_project4/taske_E_224.pdf",dpi=300)
    plt.show()

    plt.figure(figsize=(w,h))
    plt.plot(data40[:,0],data40[:,5],'x-',label='L=40')
    plt.plot(data40[:,0],data60[:,5],'x-',label='L=60')
    plt.plot(data40[:,0],data80[:,5],'x-',label='L=80')
    plt.plot(data40[:,0],data100[:,5],'x-',label='L=100')
    plt.plot(data40[:,0],data120[:,5],'x-',label='L=120')
    plt.xlabel('Temperature [kJ/T]')
    plt.ylabel(r'$\langle |M| \rangle$')
    plt.legend()
    plt.tight_layout()
    plt.savefig("/home/ejhusom/MEGAsync/FAM/FYS3150/project4/report_project4/taske_Mabs_224.pdf",dpi=300)
    plt.show()

    plt.figure(figsize=(w,h))
    plt.plot(data40[:,0],data40[:,6],'x-',label='L=40')
    plt.plot(data40[:,0],data60[:,6],'x-',label='L=60')
    plt.plot(data40[:,0],data80[:,6],'x-',label='L=80')
    plt.plot(data40[:,0],data100[:,6],'x-',label='L=100')
    plt.plot(data40[:,0],data120[:,6],'x-',label='L=120')
    plt.xlabel('Temperature [kJ/T]')
    plt.ylabel(r'$\chi$')
    plt.legend()
    plt.tight_layout()
    plt.savefig("/home/ejhusom/MEGAsync/FAM/FYS3150/project4/report_project4/taske_Chi_224.pdf",dpi=300)
    plt.show()

    plt.figure(figsize=(w,h))
    plt.plot(data40[:,0],data40[:,7],'x-',label='L=40')
    plt.plot(data40[:,0],data60[:,7],'x-',label='L=60')
    plt.plot(data40[:,0],data80[:,7],'x-',label='L=80')
    plt.plot(data40[:,0],data100[:,7],'x-',label='L=100')
    plt.plot(data40[:,0],data120[:,7],'x-',label='L=120')
    plt.xlabel('Temperature [kJ/T]')
    plt.ylabel(r'$C_V$')
    plt.legend()
    plt.tight_layout()
    plt.savefig("/home/ejhusom/MEGAsync/FAM/FYS3150/project4/report_project4/taske_CV_224.pdf",dpi=300)
    plt.show()
if (task=='f'):
    L1 = 100
    L2 = 120
    TcL1 = 2.26
    TcL2 = 2.28
    a = L1*L2*(TcL1-TcL2)/(L2-L1)
    def Tc(L,TcL):
        return TcL - a/L
    print(Tc(L1,TcL1))
    print(Tc(L2,TcL2))
