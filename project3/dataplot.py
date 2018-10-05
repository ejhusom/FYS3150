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
verlet = np.loadtxt('EarthSunVerlet.dat')
TimePointsV, KEV, PEV, rEarthV, xPosV, yPosV = verlet[:,0], verlet[:,1], verlet[:,2], verlet[:,3], verlet[:,4], verlet[:,5]
euler = np.loadtxt('EarthSunEuler.dat')
TimePointsE, xPosE, yPosE = euler[:,0], euler[:,1], euler[:,2]

plt.figure()
plt.plot(xPosV,yPosV,label='Verlet')
plt.plot(xPosE,yPosE,'--',label='Euler')
plt.title('Earth-Sun System')
plt.xlabel('x axis []')
plt.ylabel('y axis []')
plt.legend()
plt.tight_layout()
# plt.savefig("title.pdf",dpi=300)
plt.show()

plt.figure()
plt.plot(TimePointsV,KEV)
ax = plt.gca()
ax.ticklabel_format(useOffset=False)
plt.axis([0,1.1,0,70.1])
plt.title('Earth-Sun System, Total Energy Earth')
plt.xlabel('x axis []')
plt.ylabel('y axis []')
plt.tight_layout()
# plt.savefig("title.pdf",dpi=300)
plt.show()
#
# plt.figure()
# plt.plot(TimePointsV,rEarthV)
# ax = plt.gca()
# ax.ticklabel_format(useOffset=False)
# plt.axis([0,1.1,0,1.1])
# plt.title('Earth-Sun System, Distance from Sun')
# plt.xlabel('x axis []')
# plt.ylabel('y axis []')
# plt.tight_layout()
# # plt.savefig("title.pdf",dpi=300)
# plt.show()
