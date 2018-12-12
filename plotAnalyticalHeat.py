import numpy as np
import matplotlib.pyplot as plt

# data2 = np.loadtxt("HeatEquationNoQ.dat")
data2 = np.loadtxt("HeatEquationNoSlab.dat")
# data2 = np.loadtxt("HeatEquationSlab.dat")
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

Tmatrix = np.zeros((127,102))
for i in range(127):
    Tmatrix[i,:] = T2





plt.plot(y,T)
plt.plot(y,T2)
plt.plot(y,T3)
plt.show()

NoSlabSS = data2[-Nx:,:]

NoSlabSS = NoSlabSS.transpose()
NoSlabSS = np.flip(NoSlabSS)
Tmatrix = Tmatrix.transpose()
Tmatrix = np.flip(Tmatrix)
NoSlabSS = NoSlabSS*1300

fig = plt.figure()
plt.pcolormesh(NoSlabSS)
plt.colorbar()
plt.savefig('NoSlab.png')
plt.show()
plt.pcolormesh(Tmatrix)
plt.colorbar()
plt.savefig('Tmatrix.png')
plt.show()

ErrorMat = abs(Tmatrix - NoSlabSS)
plt.pcolormesh(ErrorMat)
plt.colorbar()
plt.show()

np.savetxt("landscape.dat", ErrorMat)
