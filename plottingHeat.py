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
L = 1
N = 100
dx = L/(N)
dt = 0.001
Time = 0.5
if (run=='y'):
    os.system('make')
    print('Running project...')
    # mpirun -n 4
    os.system('./runproject5.exe ' + str(method) + ' ' + str(N) + ' ' + str(dt) + ' ' + str(Time) + ' 3')
    print("Done! Moving on to plotting...")

data = np.loadtxt("HeatEquation.dat")

# Plotting
Ny = int(len(data[0,:]))
Nx = int(1.25*(Ny-2) +2)
T = int(len(data[:,0])/Nx)
timepoints = np.linspace(0,Time,T+1)


#===========================================================================
# MESH ANIMATION

# Uncomment if you want frame by frame
# fig = plt.figure()
# plt.pcolormesh(data[0:Nx,:])
# for t in range(T):
#     plt.title('Time: ' + str(timepoints[t]))
#     plt.pcolormesh(data[t*Nx:(t+1)*Nx,:])
#     plt.colorbar()
#     plt.show()

fig = plt.figure()
mat = np.transpose(data[0:Nx,:])
mat = np.flip(mat,0)
plt.pcolormesh(mat)
plt.colorbar()

def animate(t):
    plt.title('Time: ' + str(timepoints[t]))
    mat = np.transpose(data[t*Nx:(t+1)*Nx,:])
    mat = np.flip(mat,0)
    plt.pcolormesh(mat)#, vmin=0., vmax=1.)

ani = animation.FuncAnimation(fig, animate, frames = range(T), blit = False, interval=150)
# ani.save('heatMeshAnimationQ.mp4')
plt.show()
