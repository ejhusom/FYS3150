#!/usr/bin/env python
# -*- coding: utf-8 -*-
#==============================================================================
# Title:           FYS3150 Project 3a
# Author:          Erik Johannes B. L. G. Husom
# Date:            2018-00-00
# Version:         0.1
# Python version:  Python 3.6.4
# Description:
# USAGE:
#==============================================================================
# IMPORT STATEMENTS
import numpy as np
import matplotlib.pyplot as plt
# SET PLOT STYLE
plt.style.use('ggplot')
# plt.rcParams.update({'font.size': 8})
# plt.rc("text", usetex=True)
# w = 5; h = 5
# LOAD DATA
verlet = np.loadtxt('Verlet.dat')
TimePointsV, KEV, PEV, AngV, rEarthV, xPosV, yPosV = verlet[:,0], verlet[:,1], verlet[:,2], verlet[:,3], verlet[:,4], verlet[:,5], verlet[:,6]
euler = np.loadtxt('Euler.dat')
TimePointsE, KEE, PEE, AngE, rEarthE, xPosE, yPosE = euler[:,0], euler[:,1], euler[:,2], euler[:,3], euler[:,4], euler[:,5], euler[:,6]
# POSITION
plt.figure()
plt.plot(xPosV,yPosV,label='Verlet')
plt.plot(xPosE,yPosE,'--',label='Euler')
plt.title('Earth Position')
plt.xlabel('x axis [AU]')
plt.ylabel('y axis [AU]')
plt.legend()
plt.tight_layout()
# plt.savefig("title.pdf",dpi=300)
plt.show()
# TOTAL ENERGY
plt.figure()
plt.plot(TimePointsV,PEV+KEV,label='Verlet')
plt.plot(TimePointsE,PEE+KEE,'--',label='Euler')
ax = plt.gca()
ax.ticklabel_format(useOffset=False)
plt.axis([0,1.1,0,70.1])
plt.title('Total Energy Earth')
plt.legend()
plt.xlabel('time [year]')
plt.ylabel('Energy per mass')
plt.tight_layout()
# plt.savefig("title.pdf",dpi=300)
plt.show()
# ANGULAR MOMENT
plt.figure()
plt.plot(TimePointsV,AngV,label='Verlet')
plt.plot(TimePointsE,AngE,'--',label='Euler')
plt.title('Angular moment')
plt.xlabel('time [year]')
plt.ylabel('Energy per mass')
plt.legend()
plt.tight_layout()
# plt.savefig("title.pdf",dpi=300)
plt.show()
