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
Time = 1.0
if (run=='y'):
    os.system('make')
    print('Running project...')
    # mpirun -n 4
    os.system('./runproject5.exe ' + str(method) + ' ' + str(N) + ' ' + str(dt) + ' ' + str(Time) + ' 3')
    print("Done! Moving on to plotting...")

# data1 = np.loadtxt("HeatEquationNoQ.dat")
data2 = np.loadtxt("HeatEquationNoSlab.dat")
data3 = np.loadtxt("HeatEquationSlab.dat")
# data4 = np.loadtxt("HeatEquationSlabFromSS.dat")


# Plotting
Ny = int(len(data3[0,:]))
Nx = int(1.25*(Ny-2) +2)
T = int(len(data3[:,0])/Nx)
timepoints = np.linspace(0,Time,T)


#===========================================================================
# MESH ANIMATION

# Uncomment if you want frame by frame
# fig = plt.figure()
# plt.pcolormesh(data3[0:Nx,:])
# plt.show()
# for t in range(T):
#     plt.title('Time: ' + str(timepoints[t]))
#     plt.pcolormesh(data3[t*Nx:(t+1)*Nx,:])
#     plt.colorbar()
#     plt.show()

# fig = plt.figure()
# mat = np.transpose(data3[0:Nx,:])
# mat = np.flip(mat,0)
# plt.pcolormesh(mat, vmin=0., vmax=2)
# plt.colorbar()
#
# def animate(t):
#     plt.title('Time: ' + str(timepoints[t]))
#     mat = np.transpose(data3[t*Nx:(t+1)*Nx,:])
#     mat = np.flip(mat,0)
#     plt.pcolormesh(mat, vmin=0., vmax=2)
#
# ani = animation.FuncAnimation(fig, animate, frames = range(T), blit = False, interval=150)
# ani.save('heatMeshAnimationQ.gif', writer='imagemagick')
# plt.show()

#============================================================================
# 1D line slice

# steadyStateQ = data2[10*Nx:(10+1)*Nx,:]
# print(np.shape(steadyStateQ))

# np.savetxt("HeatEquationSteadyStateQ.dat", steadyStateQ)

# maxDiff = []

# for()

# lastState1 = data1[-Nx:,:]
# lineSlice1 = lastState1[int(Ny/2),:]

lastState2 = data2[-Nx:,:]
# lineSlice2 = lastState2[int(Ny/2),:]
#
lastState3 = data3[-Nx:,:]
u2 = lastState2*1300
u3 = lastState3*1300
diff = np.abs(u2-u3)

fig = plt.figure()
# diff = np.flip(diff,0)
diff = np.transpose(diff)
# np.rot90(diff)

print(np.shape(diff))
print(np.mean(diff))

# lineSlice3 = lastState3[int(Ny/2),:]
X = np.linspace(0, 150, 127)
Y = np.linspace(0, 120, 102)
X, Y =  np.meshgrid(X, Y)

plt.pcolormesh(X, Y, diff)
cbar = plt.colorbar()
cbar.set_ticks([0, 30, 60, 90, 120, 150, 180])
cbar.ax.tick_params(labelsize=labelSize, rotation=30)
cbar.set_label(r"$u$ [$^\circ$C]", size=labelSize)


# plt.pcolormesh(mat, vmin=0., vmax=2)
# plt.colorbar().ax.set_yticklabels(["20", "25", "50", "80", "110", "130", "160"])

# cbar.ax.set_yticklabels(['< -1', '0', '> 1'])

# cbar = fig.colorbar(cax, ticks=[-1, 0, 1])
#
# errorQnoSlab = np.loadtxt("HeatEquationNoSlab.dat")
# errorQnoSlab = np.flip(errorQnoSlab, 0)
#
# X = np.linspace(0, 150, 127)
# Y = np.linspace(0, 120, 102)
#
# X, Y, np.meshgrid(X, Y)
#
# plt.pcolormesh(X, Y, errorQnoSlab)
# plt.colorbar()
# plt.xticks(size=tickSize-15)
# plt.yticks(size=tickSize-15)
# # plt.xlabel(r"$y$ [km]", size=labelSize)
# # plt.ylabel(r"$u$ [$^\circ$C]", size=labelSize)
# plt.ylabel(r"$y$ [km]", size=labelSize-10)
# plt.xlabel(r"$x$ [km]", size=labelSize-10)
# plt.legend(fontsize=legendSize)
# plt.xticks(np.arange(0, 150, 15))





#
# lastState4 = data4[-Nx:,:]
# lineSlice4 = lastState4[int(Ny/2),:]
#
#
# yVals = np.linspace(0, 120, len(lineSlice2))
# u1 = lineSlice1*1300
# u2 = lineSlice2*1300
# u3 = lineSlice3*1300

# avg = sum(abs(u2-u3))/len(u3)

#
# print (avg)
# print(u2 - u3)
#
# plt.plot(yVals, abs(u2-u3))
# plt.show()

#
# diff = abs(u2 - u3);

# plt.figure()
# plt.plot(yVals, diff)
# # plt.plot(yVals, u1, label=r"No $Q$")
# # plt.plot(yVals, u2, label="$Q$")
# # plt.plot(yVals, u3, label="Slab")
#
plt.xticks(size=tickSize, rotation=30)
plt.yticks(size=tickSize, rotation=30)
# # plt.xlabel(r"$y$ [km]", size=labelSize)
# # plt.ylabel(r"$u$ [$^\circ$C]", size=labelSize)
plt.ylabel(r"$y$ [km]", size=labelSize)
plt.xlabel(r"$x$ [km]", size=labelSize)
# plt.legend(fontsize=legendSize)
plt.tight_layout()
plt.savefig("diffSlabNoSlab.pdf")
#
#
plt.show()
