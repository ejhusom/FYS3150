import numpy as np
import matplotlib.pyplot as plt

plt.rc('text', usetex=True) # LaTeX font on plots
plt.rc('font', family='serif')
fontSize = 28
tickSize = fontSize - 2
legendSize = fontSize - 6
labelSize = fontSize

data1 = np.loadtxt("HeatEquationNoQ.dat")
data2 = np.loadtxt("HeatEquationNoSlab.dat")
data3 = np.loadtxt("HeatEquationSlab.dat")
# data4 = np.loadtxt("HeatEquationSlabFromSS.dat")

def analyticalNoSlab(y):
    T = np.empty_like(y)
    a = np.array([-0.28,-0.07,-0.01])
    b = np.array([-23.66,-15.26,-10.46])
    c = np.array([8,92,188])

    i1 = int(len(y)/6)
    i2 = int(2*len(y)/6)

    T[:i1] = a[0]*y[:i1]**2 + b[0]*y[:i1]  + c[0]
    T[i1:i2] = a[1]*y[i1:i2]**2 + b[1]*y[i1:i2]  + c[1]
    T[i2:] = a[2]*y[i2:]**2 + b[2]*y[i2:]  + c[2]
    return T

def analyticalSlab(y):
    T = np.empty_like(y)
    a = np.array([-0.28,-0.07,-0.11])
    b = np.array([-29,-20.6,-23.8])
    c = np.array([8,92,28])

    i1 = int(len(y)/6)
    i2 = int(2*len(y)/6)

    T[:i1] = a[0]*y[:i1]**2 + b[0]*y[:i1]  + c[0]
    T[i1:i2] = a[1]*y[i1:i2]**2 + b[1]*y[i1:i2]  + c[1]
    T[i2:] = a[2]*y[i2:]**2 + b[2]*y[i2:]  + c[2]
    return T

def analyticalNoQ(y):
    T = np.empty_like(y)

    return 8 - y*10.7666667

Time = 1.0
Ny = int(len(data2[0,:]))
Nx = int(1.25*(Ny-2) +2)
T = int(len(data2[:,0])/Nx)
timepoints = np.linspace(0,Time,T)

y = np.linspace(0,121,102)
y = -y
T = analyticalNoSlab(y)
T2 = analyticalSlab(y)
T3 = analyticalNoQ(y)
# np.savetxt("analyticalSlab.dat", T2/1300.0)


Tmatrix = np.zeros((127,102))
for i in range(127):
    Tmatrix[i,:] = T2




#########################



##########simulated slice
lastState1 = data1[-Nx:,:]
lineSlice1 = lastState1[int(Ny/2),:]
lastState2 = data2[-Nx:,:]
lineSlice2 = lastState2[int(Ny/2),:]
lastState3 = data3[-Nx:,:]
lineSlice3 = lastState3[int(Ny/2),:]
u1 = lineSlice1*1300
u2 = lineSlice2*1300
u3 = lineSlice3*1300
# u1 = np.flip(u1)
# u2 = np.flip(u2)
# u3 = np.flip(u3)
# #
# y=-y
# #
# plt.plot(y, u1, label="No Q")
# plt.plot(y, u2, label="Q")
# plt.plot(y, u3, label="Slab")
# # plt.title("sim")
# plt.xticks(size=tickSize, rotation=30)
# plt.yticks(size=tickSize, rotation=30)
#
# plt.ylabel(r"$u$ [$^\circ$C]", size=labelSize)
# plt.xlabel(r"$y$ [km]", size=labelSize)
# plt.legend(fontsize=legendSize)
# # plt.legend(fontsize=legendSize)
# plt.tight_layout()
# plt.savefig("simulatedSlice.pdf")
# plt.show()
########################

#######relative error
diff1 = np.abs((u1 - T3)/T3)
diff2 = np.abs((u2 - T)/T)
diff3 = np.abs((u3 - T2)/T2)
plt.xticks(size=tickSize, rotation=30)
plt.yticks(size=tickSize, rotation=30)
plt.semilogy(y, diff1, label="No Q")
plt.semilogy(y, diff2, label="Q")
plt.semilogy(y, diff3, label="Slab")
plt.legend(fontsize=legendSize)
# plt.title("diff")
plt.ylabel(r"Relative error", size=labelSize)
plt.xlabel(r"$y$ [km]", size=labelSize)
plt.tight_layout()
plt.savefig("errorsSlice.pdf")
plt.show()

#########################


######### analytical slice
# y = -y
# T = np.flip(T)
# T2 = np.flip(T2)
# T3 = np.flip(T3)
# plt.plot(y,T3, label="No Q")
# plt.plot(y,T, label="Q")
# plt.plot(y,T2, label="Slab")
# plt.xticks(size=tickSize, rotation=30)
# plt.yticks(size=tickSize, rotation=30)
# plt.ylabel(r"$u$ [$^\circ$C]", size=labelSize)
# plt.xlabel(r"$y$ [km]", size=labelSize)
# # plt.title("anal")
# plt.tight_layout()
# plt.legend(fontsize=legendSize)
# plt.savefig("analyticalSlice.pdf")
# plt.show()
#####

###contour plots
# X = np.linspace(0, 150, 127)
# Y = np.linspace(0, 120, 102)
# X, Y, np.meshgrid(X, Y)
#
# NoSlabSS = data2[-Nx:,:]
#
# NoSlabSS = NoSlabSS.transpose()
# NoSlabSS = np.flip(NoSlabSS)
# Tmatrix = Tmatrix.transpose()
# Tmatrix = np.flip(Tmatrix)
# NoSlabSS = NoSlabSS*1300
#
# ErrorMat = abs((Tmatrix - NoSlabSS))
# fig = plt.figure()
# plt.pcolormesh(X, Y, NoSlabSS)
# # plt.colorbar()
# plt.xticks(size=tickSize,rotation=30)
# plt.yticks(size=tickSize,rotation=30)
# plt.xlabel(r"$x$ [km]", size=labelSize)
# plt.ylabel(r"$y$ [km]", size=labelSize)
# cb = plt.colorbar(label=r"$u$ [$^\circ$C]", ticks=[100, 500, 900, 1300])
# cb.ax.tick_params(labelsize = labelSize,rotation=30 )
# cb.set_label(label=r"$u$ [$^\circ$C]", size=labelSize )
# # cb.set_label(label=r"Relative error", size=labelSize )
# # ax = cb.ax
# # text = ax.yaxis.label
# # font = matplotlib.font_manager.FontProperties(family='times new roman', style='italic', size=16)
#
# plt.tight_layout()
# plt.savefig('SlabSteadyState.png')
# plt.show()
# plt.pcolormesh(Tmatrix)
# plt.colorbar()
# plt.savefig('Tmatrix.png')
# plt.show()
#
# ErrorMat = abs(Tmatrix - NoSlabSS)
# plt.pcolormesh(ErrorMat)
# plt.colorbar()
# plt.show()
#
# np.savetxt("landscape.dat", ErrorMat)
