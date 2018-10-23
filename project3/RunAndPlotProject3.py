#!/usr/bin/env python
# -*- coding: utf-8 -*-
#==============================================================================
# Title:           FYS3150 Project 3 - Running and plotting Solar System
# Author:          Erik Johannes B. L. G. Husom
# Date:            2018-10-11
# Version:         2.0
# Python version:  Python 3.6.4
# Description: Run and plot project 3.
# USAGE: All info will be provided when script is run in the terminal.
#==============================================================================
# IMPORT STATEMENTS
import numpy as np
import sys, os
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
# SET PLOT STYLE
plt.style.use('ggplot')
plt.rcParams.update({'font.size': 8})
plt.rcParams['text.latex.preamble'] = [r'\usepackage{amsmath}']
plt.rc("text", usetex=True)
w = 5; h = 2.5

# USER INPUT
rows, columns = os.popen('stty size', 'r').read().split()
for i in range(int(columns)):
    print('=',end='')
print("FYS3150 Project 3 - Simulation of the Solar System")
print('Run simulation and produce data files? Enter \'n\' to move on to plotting.')
run = input('y/n=')

if (run=="y"):
    System = input('Both (0), Solar system (1), Sun/Earth (2) or Sun/Mercury (3)=')
    MeshPoints = input('Number of mesh points (give zero to use default values for mesh points and simulation years)=')
    if (MeshPoints!='0'):
        TimeFinal = input('Number of years to simulate=')
        os.system('make')
        print('Running project...')
        os.system('./runproject3.x ' + System + ' ' + MeshPoints + ' ' + TimeFinal)
    else:
        os.system('make')
        print('Running project...')
        os.system('./runproject3.x ' + System)


for i in range(int(columns)):
    print('=',end='')
print("What do you want to plot? Give integer as input, among the following options:")
print("0: Do not plot, exit program")
print("1: Solar system in 3D, Verlet method")
print("2: Two body problem (Sun and Earth) in 2D, Verlet and Euler method")
print("3: Two body problem (Sun and Mercury) with relativistic force")
choice = float(input('Input='))

if (choice==1):
    ObjectPositions = np.loadtxt('SolarSystemVerlet.dat')
    objectNames = np.array(['Sun', 'Mercury', 'Venus', 'Earth', 'Mars', 'Jupiter', 'Saturn', 'Uranus', 'Neptune', 'Pluto'])

    # PLOT
    fig = plt.figure(figsize=(5,4))
    ax = fig.gca(projection='3d')
    # ax.set_aspect('equal')

    for i in range(np.size(objectNames)):
        plt.plot(ObjectPositions[:,i*3], ObjectPositions[:,i*3+1], ObjectPositions[:,i*3+2], label=objectNames[i])

    plt.xlabel('x axis [AU]')
    plt.ylabel('y axis [AU]')
    ax.set_zlabel('z axis [AU]')
    plt.legend()
    # plt.tight_layout()
    plt.savefig("SolarSystemVerletPositions.pdf",dpi=300)
    plt.show()
elif (choice==2):
    verlet = np.loadtxt('TwoBodyProblemVerlet.dat')
    TimePointsV, KEV, PEV, AngV, rEarthV, xPosV, yPosV = verlet[:,0], verlet[:,1], verlet[:,2], verlet[:,3], verlet[:,4], verlet[:,5], verlet[:,6]
    euler = np.loadtxt('TwoBodyProblemEuler.dat')
    TimePointsE, KEE, PEE, AngE, rEarthE, xPosE, yPosE = euler[:,0], euler[:,1], euler[:,2], euler[:,3], euler[:,4], euler[:,5], euler[:,6]
    Vh01 = np.loadtxt('TwoBodyProblemVerletH10.dat')
    Vh001 = np.loadtxt('TwoBodyProblemVerletH100.dat')
    Vh0001 = np.loadtxt('TwoBodyProblemVerletH1000.dat')
    Vh00001 = np.loadtxt('TwoBodyProblemVerletH10000.dat')
    Eh01 = np.loadtxt('TwoBodyProblemEulerH10.dat')
    Eh001 = np.loadtxt('TwoBodyProblemEulerH100.dat')
    Eh0001 = np.loadtxt('TwoBodyProblemEulerH1000.dat')
    Eh00001 = np.loadtxt('TwoBodyProblemEulerH10000.dat')
    tVh01, xVh01, yVh01 = Vh01[:,0], Vh01[:,5], Vh01[:,6]
    tVh001, xVh001, yVh001 = Vh001[:,0], Vh001[:,5], Vh001[:,6]
    tVh0001, xVh0001, yVh0001 = Vh0001[:,0], Vh0001[:,5], Vh0001[:,6]
    tVh00001, xVh00001, yVh00001 = Vh00001[:,0], Vh00001[:,5], Vh00001[:,6]
    tEh01, xEh01, yEh01 = Eh01[:,0], Eh01[:,5], Eh01[:,6]
    tEh001, xEh001, yEh001 = Eh001[:,0], Eh001[:,5], Eh001[:,6]
    tEh0001, xEh0001, yEh0001 = Eh0001[:,0], Eh0001[:,5], Eh0001[:,6]
    tEh00001, xEh00001, yEh00001 = Eh00001[:,0], Eh00001[:,5], Eh00001[:,6]
    # POSITION
    plt.figure(figsize=(w,h))
    # plt.plot(xVh01, yVh01, label='h = 0.1', LineWidth=0.5)
    plt.plot(xVh001, yVh001, '--', label='h = 0.01', LineWidth=0.5)
    plt.plot(xVh0001, yVh0001, '--', label='h = 0.001', LineWidth=0.5)
    plt.plot(xVh00001, yVh00001, '--', label='h = 0.0001', LineWidth=0.5)
    plt.xlabel('x axis [AU]')
    plt.ylabel('y axis [AU]')
    plt.axis('equal')
    plt.legend()
    plt.tight_layout()
    plt.savefig("TwoBodyProblemVerletPosition.pdf",dpi=300)
    plt.show()
    plt.figure(figsize=(w,h))
    # plt.plot(xVh01, yEh01, label='h = 0.1', LineWidth=0.5)
    plt.plot(xEh001, yEh001, label='h = 0.01', LineWidth=0.5)
    plt.plot(xEh0001, yEh0001, label='h = 0.001', LineWidth=0.5)
    plt.plot(xEh00001, yEh00001, label='h = 0.0001', LineWidth=0.5)
    plt.xlabel('x axis [AU]')
    plt.ylabel('y axis [AU]')
    plt.axis('equal')
    plt.legend()
    plt.tight_layout()
    plt.savefig("TwoBodyProblemEulerPosition.pdf",dpi=300)
    plt.show()
    # TOTAL ENERGY
    plt.figure(figsize=(w,h))
    plt.plot(TimePointsV,PEV+KEV,label='Verlet')
    plt.plot(TimePointsE,PEE+KEE,'--',label='Euler')
    plt.legend()
    plt.xlabel('time [year]')
    plt.ylabel(r"Total Energy [$M_{\mathrm{Sun}}\mathrm{AU}^2\mathrm{yr}^{-2}$]")
    plt.tight_layout()
    plt.savefig("TwoBodyProblemTotalEnergy.pdf",dpi=300)
    plt.show()
    # ANGULAR MOMENT
    plt.figure(figsize=(w,h))
    plt.plot(TimePointsV,AngV,label='Verlet')
    plt.plot(TimePointsE,AngE,'--',label='Euler')
    plt.xlabel('time [year]')
    plt.ylabel(r"Angular Moment / mass [$\mathrm{AU}^2\mathrm{yr}^{-2}$]")
    plt.legend()
    plt.tight_layout()
    plt.savefig("TwoBodyProblemAngular.pdf",dpi=300)
    plt.show()
elif (choice==3):
    Precession = np.loadtxt('MercuryPrecession.dat')
    PrecessionNon = np.loadtxt('MercuryPrecessionNon.dat')
    t = Precession[:,0]
    tNon = PrecessionNon[:,0]
    arcsec = 3600*np.arctan(Precession[:,1])*180/np.pi
    arcsecNon = 3600*np.arctan(PrecessionNon[:,1])*180/np.pi

    coeff = np.polyfit(t,arcsec,1)
    p = np.poly1d(coeff)
    coeffNon = np.polyfit(tNon,arcsecNon,1)
    pNon = np.poly1d(coeffNon)

    print("Perihelion precession per century: ", p(t[-1])-p(t[0]))
    print("Number of revolutions: ", np.size(arcsec))
    print("Perihelion precession per century (non-relativistic): ", pNon(t[-1])-pNon(t[0]))
    print("Number of revolutions (non-relativistic): ", np.size(arcsecNon))

    # PRECESSION
    plt.figure(figsize=(w,h))
    plt.plot(Precession[:,0], 3600*np.arctan(Precession[:,1])*180/np.pi,'.-',label='perihelion precession', LineWidth=0.4, markersize=0.3)
    plt.plot(PrecessionNon[:,0], 3600*np.arctan(PrecessionNon[:,1])*180/np.pi,'.-',label='perihelion precession (non-relativistic)', LineWidth=0.4, markersize=0.3)
    plt.plot(t,p(t),label='linear fit')
    plt.plot(tNon,pNon(t),label='linear fit (non-relativistic)')
    plt.xlabel('time [year]')
    plt.ylabel('arcseconds')
    plt.legend()
    plt.tight_layout()
    plt.savefig("MercuryPrecessionBoth.pdf",dpi=300)
    plt.show()
