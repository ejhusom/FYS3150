#!/usr/bin/env python
# -*- coding: utf-8 -*-
#==========================================================================
# Program by Erik Johannes B. L. G. Husom on 2018-11-01 for Python 3.6.4
# Description: Run and plot project 4 in FYS3150
# USAGE:
#==========================================================================
# IMPORT STATEMENTS
import numpy as np
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
print('Run simulation and produce data files? Enter \'n\' to move on to plotting.')
run = input('y/n=')

if (run=="y" ):
    print("4b")
    print("4c")
    print("4d")
    print("4e")
    task = input('Which task=')
    os.system('make')
    print('Running project...')
    os.system('mpirun -n 4 ./runproject4.x ')


for i in range(int(columns)):
    print('=',end='')
print("What do you want to plot? Give integer as input, among the following options:")
print("0: Do not plot, exit program")
print("1: Solar system in 3D, Verlet method")
print("2: Two body problem (Sun and Earth) in 2D, Verlet and Euler method")
print("3: Two body problem (Sun and Mercury) with relativistic force")
plotchoice = float(input('Input='))