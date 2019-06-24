verlet = np.loadtxt('TwoBodyProblemVerlet.dat')
TimePointsV, KEV, PEV, AngV, rEarthV, xPosV, yPosV = verlet[:,0], verlet[:,1], verlet[:,2], verlet[:,3], verlet[:,4], verlet[:,5], verlet[:,6]
verlet13 = np.loadtxt('TwoBodyProblemVerlet13.dat')
TimePointsV13, xPosV13, yPosV13 = verlet13[:,0], verlet13[:,5], verlet13[:,6]
verlet14 = np.loadtxt('TwoBodyProblemVerlet14.dat')
TimePointsV14, xPosV14, yPosV14 = verlet14[:,0], verlet14[:,5], verlet14[:,6]
verletSqrt2 = np.loadtxt('TwoBodyProblemVerletSqrt2.dat')
TimePointsVSqrt2, xPosVSqrt2, yPosVSqrt2 = verletSqrt2[:,0], verletSqrt2[:,5], verletSqrt2[:,6]
verlet15 = np.loadtxt('TwoBodyProblemVerlet15.dat')
TimePointsV15, xPosV15, yPosV15 = verlet15[:,0], verlet15[:,5], verlet15[:,6]
plt.figure(figsize=(w,h))
plt.plot(xPosV,yPosV,label='$v = 2\pi$')
plt.plot(xPosV13,yPosV13,label='$v = 1.3 \cdot 2\pi$')
plt.plot(xPosV14,yPosV14,label='$v = 1.4 \cdot 2\pi$')
plt.plot(xPosVSqrt2,yPosVSqrt2,label='$v =\sqrt{2} \cdot 2\pi$')
# plt.plot(xPosV15,yPosV15,label='$v = 1.5 \cdot 2\pi$')
plt.xlabel('x axis [AU]')
plt.ylabel('y axis [AU]')
plt.axis('equal')
plt.legend()
plt.tight_layout()
plt.savefig("TwoBodyProblemEscape.pdf",dpi=300)
plt.show()
