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

print('Run simulation and produce data files? Enter \'n\' to move on to plotting.')
run = input('y/n=')
method = 1
N = 100
dx = 0.01
# dt = 0.25*dx*dx;
dt = 0.001
Time = 0.3
if (run=='y'):
    os.system('make')
    print('Running project...')
    # mpirun -n 4
    os.system('./runproject5.exe ' + str(method) + ' ' + str(N) + ' ' + str(dt) + ' ' + str(Time) + ' 2')
    print("Done! Moving on to plotting...")
# data = np.loadtxt("Jacobi2DN200.dat")
data = np.loadtxt("Implicit2DN" + str(N) + ".dat")
# data = np.loadtxt("morten1.dat")

# Plotting
N = int(len(data[0,:]))
T = int(len(data[:,0])/N)
timepoints = np.linspace(0,Time,T+1)

# #===========================================================================
# MESH ANIMATION


# plt.pcolormesh(data[-N:,:])
# plt.colorbar()
# plt.show()

# print(len(data[:,0]))


# fig = plt.figure()
# # plt.pcolormesh(data[0:N,:], vmin=0., vmax=1.)
# # for t in range(T):
# #     plt.title('Time: ' + str(timepoints[t]))
# #     plt.pcolormesh(data[t*N:(t+1)*N,:], vmin=0., vmax=1.)
# #     plt.colorbar()
# #     plt.show()
#
#
# plt.pcolormesh(data[0:N,:],vmin=0., vmax=1.)
# plt.colorbar()
#
# def animate(t):
#     plt.title('Time: ' + str(timepoints[t]))
#     plt.pcolormesh(data[t*N:(t+1)*N,:], vmin=0., vmax=1.)
#
# ani = animation.FuncAnimation(fig, animate, frames = range(T), blit = False, interval=200)
# ani.save('diffusionMeshAnimation.mp4')
# plt.show()


#=============================================================================
# ANALYTICAL 2D SOLUTION
# x = np.linspace(0,1,80)
# y = np.linspace(0,1,80)
# X, Y = np.meshgrid(x,y)
#
# t = np.linspace(0,0.2,51)
#
# fig = plt.figure()
#
# def u(X,Y,t):
#     return np.sin(np.pi*X)*np.sin(np.pi*Y)*np.exp(-2*np.pi**2*t)
#
# plt.pcolormesh(X,Y,u(X,Y,t[0]), vmin=0., vmax=1.)
# plt.colorbar()
#
# def animate(i):
#     print(t[i])
#     plt.title('Time: ' + str(t[i]))
#     plt.pcolormesh(X,Y,u(x,Y,t[i]), vmin=0., vmax=1.)
#
# ani = animation.FuncAnimation(fig, animate, frames = range(len(t)), blit = False, interval=200)
# ani.save('diffusionMeshAnimationAnalytical.mp4')
#
#
# plt.show()
