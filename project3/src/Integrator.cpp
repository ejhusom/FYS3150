// #include <iostream>
// #include <fstream>
// #include <iomanip>
// #include <cmath>
// #include <string>
// #include "Integrator.h"
//
// using namespace std;
//
// void initialize(int MeshPoints, double TimeFinal){
//   double TimeStep = TimeFinal/double(MeshPoints);
//   double TimeStepSq = TimeStep*TimeStep;
//   double TimeStepHalf = TimeStep/2;
//   double TimeStepSqHalf = TimeStepSq/2;
//   double FourPiSq = 4*M_PI*M_PI;
//   // Arrays
//   double *Distance = new double[MeshPoints];
//   double *xPos = new double[MeshPoints];
//   double *yPos = new double[MeshPoints];
//   double *xVel = new double[MeshPoints];
//   double *yVel = new double[MeshPoints];
//   double *xAcc = new double[MeshPoints];
//   double *yAcc = new double[MeshPoints];
//   double *TimePoints = new double[MeshPoints];
//   double *KineticEnergy = new double[MeshPoints];
//   double *PotentialEnergy = new double[MeshPoints];
//   double *AngularMoment = new double[MeshPoints];
//   // Initial values
//   Distance[0] = 1;
//   xPos[0] = 1;
//   yPos[0] = 0;
//   xVel[0] = 0;
//   yVel[0] = 2*M_PI;
//   TimePoints[0] = 0;
//
// }
