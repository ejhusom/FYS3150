import matplotlib.pyplot as plt
import numpy as np
import sys, os
fontSize = 28
tickSize = fontSize - 2
legendSize = fontSize - 6
labelSize = fontSize

# USER INPUT
print('Which method?')
print('Explicit/Forward Euler=0')
print('Implicit/Backward Euler=1')
print('Crank-Nicolson=2')
method = input('Method=')

if (method=='0'):
    N = 1000
    methodName = "Explicit"
    Time = 1
    dt = 0.001
    T = Time/dt
if (method=='1'):
    N = 100
    methodName = "Implicit"
    Time = 1
    dt = 0.00001
    T = Time/dt

os.system('make')
print('Running project...')
os.system('./runproject5.exe ' + method + ' ' + str(N) + ' ' + str(dt) + ' ' + str(Time))

analytical = np.loadtxt("analytical.dat")
data = np.loadtxt(methodName + "N" + str(N) + ".dat")

# plt.plot(analytical[:,0], analytical[:,1])

x = np.linspace(0,1,N)

l = 0
while (l < T):
    plt.plot(x,data[l,:])
    l += int(T/10)

plt.xticks(size=tickSize, rotation=30)
plt.yticks(size=tickSize, rotation=30)
plt.xlabel(r"x", size=labelSize)
plt.ylabel(r"u", size=labelSize)
plt.legend(fontsize=legendSize)
plt.tight_layout()
plt.plot()
plt.show()
