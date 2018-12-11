import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import sys, os

plt.rc('text', usetex=True) # LaTeX font on plots
plt.rc('font', family='serif')
fontSize = 28
tickSize = fontSize - 2
legendSize = fontSize - 6
labelSize = fontSize

print('Which method?')
print('ForwardEuler/Explicit: 0')
print('BackwardEuler/Implicit: 1')
print('Crank-Nicolson: 0.5')
method = input('Method=')
print('Run simulation and produce data files? Enter \'n\' to move on to plotting.')
run = input('y/n=')
if (method=='0'):
    if (run=='y'):
        N = 100
        dt = 0.00001
        Time = 1
        os.system('make')
        print('Running project...')
        os.system('./runproject5.exe ' + method + ' ' + str(N) + ' ' + str(dt) + ' ' + str(Time) + '1')
    data = np.loadtxt("ExplicitN100.dat")
if (method=='1'):
    if (run=='y'):
        N = 100
        dt = 0.0001
        Time = 1
        os.system('make')
        print('Running project...')
        os.system('./runproject5.exe ' + method + ' ' + str(N) + ' ' + str(dt) + ' ' + str(Time) + ' 1')
    data = np.loadtxt("ImplicitN100.dat")
if (method=='0.5'):
    if (run=='y'):
        N = 100
        dt = 0.00001
        Time = 1
        os.system('make')
        print('Running project...')
        os.system('./runproject5.exe ' + method + ' ' + str(N) + ' ' + str(dt) + ' ' + str(Time) + '1')
    data = np.loadtxt("CrankN100.dat")

# data = np.loadtxt("Heat1DN100.dat")
# Plotting
N = len(data[0,:])
Tindex = len(data[:,0])-1
x = np.linspace(0, 1, N)
chosenTimepoints = [0,0.002,0.004,0.006,0.008,0.01,0.02,0.03,0.04,0.05,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0]

plt.figure()
for t in chosenTimepoints:
    plt.plot(x, data[int(t*Tindex),:],label=str(t))

plt.xticks(size=tickSize, rotation=30)
plt.yticks(size=tickSize, rotation=30)
plt.xlabel(r"x", size=labelSize)
plt.ylabel(r"u", size=labelSize)
plt.legend(fontsize=legendSize)
plt.tight_layout()
plt.plot()
plt.show()


#===========================================================================
# LINE ANIMATION
# fig, ax = plt.subplots()
# line, = ax.plot(x, data[0,:])
#
# def animate(Timepoint):
#     # plt.plot(data[int(Timepoint*Tindex),:])
#     ax.set_title('Time: ' + str(Timepoint))
#     line.set_ydata(data[int(Timepoint*Tindex),:])
#     return line,
#
# ani = animation.FuncAnimation(fig, animate, frames=chosenTimepoints)
# ani.save('diffusionLineAnimation.mp4')
# plt.show()

#============================================================================
# HEAT ANIMATIONN
# fig = plt.figure()
#
# ims = []
#
# for Timepoint in chosenTimepoints:
#     im = plt.imshow((data[int(Timepoint*Tindex),:],data[int(Timepoint*Tindex),:]), animated=True)
#     ims.append([im])
#
# ani = animation.ArtistAnimation(fig, ims)
# ani.save('diffusionHeatAnimation.mp4')
# plt.show()

#==========================================================================
# ANALYTICALS
# analytical = np.loadtxt("analytical.dat")
# plt.plot(analytical[:,0], analytical[:,1])
