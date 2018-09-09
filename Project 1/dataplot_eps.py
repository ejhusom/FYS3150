#!/usr/bin/env python
# -*- coding: utf-8 -*-
#==============================================================================
# Title:            Data Plot of Error
# Author:           Erik Johannes B. L. G. Husom
# Date:             2018-09-09
# Version:          3.0
# Python version:   Python 3.6.4
# DESCRIPTION: Plotting data from error-file in FYS3150 project 1
#==============================================================================
# IMPORT STATEMENTS
import numpy as np
import matplotlib.pyplot as plt
# SET PLOT STYLE
plt.style.use('ggplot')
plt.rcParams["mathtext.fontset"] = "cm"
plt.rcParams.update({'font.size': 8})
w = 5; h = 2.5
#===========================================
# LOAD DATA
data = np.loadtxt('epsilons.dat')
log10h = data[:,0]; eps = data[:,1]
# PLOT EPSILON VS H on a log-scale
plt.figure(figsize=(w,h))
plt.plot(log10h,eps, 'b-o')
plt.xlabel('$log_{10}(h)$')
plt.ylabel('$log_{10}(\epsilon)$')
plt.tight_layout()
plt.savefig("/home/ejhusom/MEGAsync/FYS3150/project1/project1_report/epsilons.png",dpi=300)
plt.show()
