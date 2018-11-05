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
print("FYS3150 Project 4 -Ising Model")
task = input('Which task (b, c, d, e, f)=')
print('Run simulation and produce data files? Enter \'n\' to move on to plotting.')
run = input('y/n=')
if (task=='b'):
    if (run==y):
        dim = 2
        state = 1
        nCycles = 1000000
        temp_init = 1.0
        temp_final = 1.1
        temp_step = 1.0
        os.system('make')
        print('Running project for task ' + task + '...')
        os.system('mpirun -n 4 ./runproject4.x ' + str(dim) + ' ' + str(state) + ' ' + str(nCycles) + ' ' + str(temp_init) + ' ' + str(temp_final) + ' ' + str(temp_step))
if (task=='c'):
    dim = 20
    states = [0,1]
    nCycles = [100,1000,10000,100000,1000000]
    temp_init = 1.0
    temp_final = 2.4
    temp_step = 1.4
    if (run=="y" ):
        os.system('make')
        print('Running project for task ' + task + '...')
        for state in states:
            for N in nCycles:
                a = 2
                os.system('mpirun -n 4 ./runproject4.x ' + str(dim) + ' ' + str(state) + ' ' + str(N) + ' ' + str(temp_init) + ' ' + str(temp_final) + ' ' + str(temp_step))
    energy1 = []
    energy2 = []
    # for state in states:
    for N in nCycles:
        data = np.loadtxt("Dim" + str(dim) + "State" + '1' + "Cycles" + str(N) + "T" + str(temp_init) + "00000.dat", skiprows=1)
        energy1.append(data[0,1])
        energy2.append(data[1,1])
    plt.figure(figsize=(w,h))
    plt.plot(nCycles,energy1,label='T=1.0')
    plt.plot(nCycles,energy2,label='T=2.4')
    plt.title('Title')
    plt.xlabel('x axis []')
    plt.ylabel('y axis []')
    plt.legend()
    plt.tight_layout()
    plt.savefig("taskc.pdf",dpi=300)
    plt.show()
