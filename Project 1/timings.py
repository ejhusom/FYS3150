#!/usr/bin/env python
# -*- coding: utf-8 -*-
#==============================================================================
# Title:           Benchmark Calculations
# Author:          Erik Johannes B. L. G. Husom
# Date:            2018-09-09
# Version:         0.1
# Python version:  Python 3.6.4
# Description:
#==============================================================================
# IMPORT STATEMENTS
import numpy as np
import matplotlib.pyplot as plt
import datetime
now = datetime.datetime.now()
#==============================================================================
# LOAD DATA
data = np.loadtxt('timings.dat')
# WRITE DATA TO FILE
outfile = open("benchmark.md","w")
outfile.write("""# Benchmark timings of project 1

- Processor: Intel® Core™ M-5Y71 CPU @ 1.20GHz × 4
- Memory: 8 GB DDR3L SDRAM @ 1600 MHz - PC3L-12800

|n    |General algorithm (s) |Specialized algorithm (s)|LU decomposition (s)|
|-----|----------------------|-------------------------|----------------|\n""")
for i in range(6):
    outfile.write("|10^{:d} ".format(i+1))
    outfile.write("| {:.7f} ".format(np.average(data[int(10*i):int(10*(i+1))])))
    outfile.write("| {:.7f} ".format(np.average(data[int(60+10*i):int(60+10*(i+1))])))
    if i<3:
        outfile.write("| {:.7f} |".format(np.average(data[int(120+10*i):int(120+10*(i+1))])))
    else:
        outfile.write("| - |")
    outfile.write("\n")
outfile.write("Run time recorded: ")
outfile.write("{:}".format(now.strftime("%Y-%m-%d %H:%M")))
outfile.close()
