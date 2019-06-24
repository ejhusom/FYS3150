    verlet = np.loadtxt('TwoBodyProblemVerlet.dat')
    TimePointsV, xPosV, yPosV = verlet[:,0][:1000], verlet[:,5][:1000], verlet[:,6][:1000]
    verlet = np.loadtxt('TwoBodyProblemVerletBeta22.dat')
    TimePointsV22, xPosV22, yPosV22 = verlet[:,0][:1000], verlet[:,5][:1000], verlet[:,6][:1000]
    verlet = np.loadtxt('TwoBodyProblemVerletBeta24.dat')
    TimePointsV24, xPosV24, yPosV24 = verlet[:,0][:1000], verlet[:,5][:1000], verlet[:,6][:1000]
    verlet = np.loadtxt('TwoBodyProblemVerletBeta26.dat')
    TimePointsV26, xPosV26, yPosV26 = verlet[:,0][:1000], verlet[:,5][:1000], verlet[:,6][:1000]
    verlet = np.loadtxt('TwoBodyProblemVerletBeta28.dat')
    TimePointsV28, xPosV28, yPosV28 = verlet[:,0][:1000], verlet[:,5][:1000], verlet[:,6][:1000]
    verlet = np.loadtxt('TwoBodyProblemVerletBeta30.dat')
    TimePointsV30, xPosV30, yPosV30 = verlet[:,0][:1000], verlet[:,5][:1000], verlet[:,6][:1000]
    # POSITION
    plt.figure(figsize=(w,h))
    plt.plot(xPosV,yPosV,'--',label=r'$\beta = 2.0$', LineWidth=0.5)
    plt.plot(xPosV22,yPosV22,'--',label=r'$\beta = 2.2$', LineWidth=0.5)
    plt.plot(xPosV24,yPosV24,'--',label=r'$\beta = 2.4$', LineWidth=0.5)
    plt.plot(xPosV26,yPosV26,'--',label=r'$\beta = 2.6$', LineWidth=0.5)
    plt.plot(xPosV28,yPosV28,'--',label=r'$\beta = 2.8$', LineWidth=0.5)
    plt.plot(xPosV30,yPosV30,'--',label=r'$\beta = 3.0$', LineWidth=0.5)
    plt.xlabel('x axis [AU]')
    plt.ylabel('y axis [AU]')
    plt.axis('equal')
    plt.legend()
    plt.tight_layout()
    plt.savefig("TwoBodyProblemBeta.pdf",dpi=300)
    plt.show()
