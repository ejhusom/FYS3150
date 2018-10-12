#!/usr/bin/env python
# -*- coding: utf-8 -*-
#==============================================================================
# Title:           FYS3150 Project 3 - Running and plotting Solar System
# Author:          Erik Johannes B. L. G. Husom
# Date:            2018-10-11
# Version:         1.0
# Python version:  Python 3.6.4
# Description:
# USAGE:
#==============================================================================
# IMPORT STATEMENTS
import numpy as np
import sys, os
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
# SET PLOT STYLE
plt.style.use('ggplot')
plt.rcParams.update({'font.size': 15})
plt.rc("text", usetex=True)
w = 15; h = 10

# USER INPUT
rows, columns = os.popen('stty size', 'r').read().split()
for i in range(int(columns)):
    print('=',end='')
print("FYS3150 Project 3 - Simlaution of the Solar System")
print('Run simulation and produce data files? Enter \'n\' to move on to plotting.')
run = input('y/n=')

if (run=="y"):
    System = input('Both (0), Solar system (1) or Two body (2)=')
    MeshPoints = input('Number of mesh points (give zero to use default values)=')
    if (MeshPoints!='0'):
        TimeFinal = input('Number of years to simulate=')
        os.system('make')
        os.system('./runproject3.x ' + System + ' ' + MeshPoints + ' ' + TimeFinal)
    else:
        os.system('make')
        os.system('./runproject3.x ' + System)

for i in range(int(columns)):
    print('=',end='')
print("What do you want to plot? Give integer as input, among the following options:")
print("0: Do not plot, exit program")
print("1: Solar system in 3D, Verlet method")
print("2: Two body problem (Sun and Earth) in 2D, Verlet and Euler method")
choice = float(input('Input='))

if (choice==1):
    ObjectPositions = np.loadtxt('SolarSystemVerletPositions.dat')
    objectNames = np.array(['Sun', 'Mercury', 'Venus', 'Earth', 'Mars', 'Jupiter', 'Saturn', 'Uranus', 'Neptune', 'Pluto'])
    # PLOT
    fig = plt.figure(figsize=(w,h))
    ax = fig.gca(projection='3d')
    ax.set_aspect('equal')

    for i in range(np.size(objectNames)):
        plt.plot(ObjectPositions[:,i*3], ObjectPositions[:,i*3+1], ObjectPositions[:,i*3+2], label=objectNames[i])

    plt.title('Position of planets')
    plt.xlabel('x axis [AU]')
    plt.ylabel('y axis [AU]')
    ax.set_zlabel('z axis [AU]')
    plt.legend()
    plt.tight_layout()
    plt.savefig("SolarSystemVerletPositions.pdf",dpi=300)
    plt.show()
elif (choice==2):
    verlet = np.loadtxt('TwoBodyProblemVerlet.dat')
    TimePointsV, KEV, PEV, AngV, rEarthV, xPosV, yPosV = verlet[:,0], verlet[:,1], verlet[:,2], verlet[:,3], verlet[:,4], verlet[:,5], verlet[:,6]
    euler = np.loadtxt('TwoBodyProblemEuler.dat')
    TimePointsE, KEE, PEE, AngE, rEarthE, xPosE, yPosE = euler[:,0], euler[:,1], euler[:,2], euler[:,3], euler[:,4], euler[:,5], euler[:,6]
    # POSITION
    plt.figure()
    plt.plot(xPosV,yPosV,label='Verlet')
    plt.plot(xPosE,yPosE,'--',label='Euler')
    plt.title('Earth Position')
    plt.xlabel('x axis [AU]')
    plt.ylabel('y axis [AU]')
    plt.axis('equal')
    plt.legend()
    plt.tight_layout()
    plt.savefig("TwoBodyProblemPosition.pdf",dpi=300)
    plt.show()
    # TOTAL ENERGY
    plt.figure()
    plt.plot(TimePointsV,PEV+KEV,label='Verlet')
    plt.plot(TimePointsE,PEE+KEE,'--',label='Euler')
    plt.title('Total Energy Earth')
    plt.legend()
    plt.xlabel('time [year]')
    plt.ylabel('Total Energy')
    plt.tight_layout()
    plt.savefig("TwoBodyProblemTotalEnergy.pdf",dpi=300)
    plt.show()
    # ANGULAR MOMENT
    plt.figure()
    plt.plot(TimePointsV,AngV,label='Verlet')
    plt.plot(TimePointsE,AngE,'--',label='Euler')
    plt.title('Angular moment')
    plt.xlabel('time [year]')
    plt.ylabel('')
    plt.legend()
    plt.tight_layout()
    plt.savefig("TwoBodyProblemAngular.pdf",dpi=300)
    plt.show()
