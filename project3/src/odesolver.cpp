#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include "odesolver.h"

using namespace std;

void odesolver::initialize(int MeshPoints, double TimeFinal){
  double TimeStep = TimeFinal/double(MeshPoints);
  double TimeStepSq = TimeStep*TimeStep;
  double TimeStepHalf = TimeStep/2;
  double TimeStepSqHalf = TimeStepSq/2;
  double FourPiSq = 4*M_PI*M_PI;
  // Arrays
  double *rEarth = new double[MeshPoints];
  double *xPos = new double[MeshPoints];
  double *yPos = new double[MeshPoints];
  double *xVel = new double[MeshPoints];
  double *yVel = new double[MeshPoints];
  double *xAcc = new double[MeshPoints];
  double *yAcc = new double[MeshPoints];
  double *TimePoints = new double[MeshPoints];
  double *KineticEnergy = new double[MeshPoints];
  double *PotentialEnergy = new double[MeshPoints];
  // Initial values
  rEarth[0] = 1;
  xPos[0] = 1;
  yPos[0] = 0;
  xVel[0] = 0;
  yVel[0] = 2*M_PI;
  TimePoints[0] = 0;
}

void odesolver::VelocityVerlet(int MeshPoints, double TimeFinal){
  double TimeStep = TimeFinal/double(MeshPoints);
  double TimeStepSq = TimeStep*TimeStep;
  double TimeStepHalf = TimeStep/2;
  double TimeStepSqHalf = TimeStepSq/2;
  double FourPiSq = 4*M_PI*M_PI;
  // Arrays
  double *rEarth = new double[MeshPoints];
  double *xPos = new double[MeshPoints];
  double *yPos = new double[MeshPoints];
  double *xVel = new double[MeshPoints];
  double *yVel = new double[MeshPoints];
  double *xAcc = new double[MeshPoints];
  double *yAcc = new double[MeshPoints];
  double *TimePoints = new double[MeshPoints];
  double *KineticEnergy = new double[MeshPoints];
  double *PotentialEnergy = new double[MeshPoints];
  double *AngularMoment = new double[MeshPoints];
  // Initial values
  rEarth[0] = 1;
  xPos[0] = 1;
  yPos[0] = 0;
  xVel[0] = 0;
  yVel[0] = 2*M_PI;
  TimePoints[0] = 0;
  // Integration loop
  double FPSDivrEarthCu;
  for (int i = 0; i < MeshPoints; i++) {
    FPSDivrEarthCu = FourPiSq/(rEarth[i]*rEarth[i]*rEarth[i]);
    xAcc[i] = -xPos[i]*FPSDivrEarthCu;
    yAcc[i] = -yPos[i]*FPSDivrEarthCu;

    xPos[i+1] = xPos[i] + TimeStep*xVel[i] + xAcc[i]*TimeStepSqHalf;
    yPos[i+1] = yPos[i] + TimeStep*yVel[i] + yAcc[i]*TimeStepSqHalf;
    rEarth[i+1] = sqrt(xPos[i+1]*xPos[i+1] + yPos[i+1]*yPos[i+1]);

    xAcc[i+1] = -xPos[i+1]*FPSDivrEarthCu;
    yAcc[i+1] = -yPos[i+1]*FPSDivrEarthCu;
    xVel[i+1] = xVel[i] + TimeStepHalf*(xAcc[i+1] + xAcc[i]);
    yVel[i+1] = yVel[i] + TimeStepHalf*(yAcc[i+1] + yAcc[i]);

    KineticEnergy[i] = (xVel[i]*xVel[i] + yVel[i]*yVel[i]);
    PotentialEnergy[i] = -1/rEarth[i];
    AngularMoment[i] = fabs(xPos[i]*xVel[i] - yPos[i]*yVel[i]);

    TimePoints[i+1] = TimePoints[i] + TimeStep;
  }
  ofstream outfile;
  outfile.open ("EarthSunVerlet.dat");
  for (int i=0; i<MeshPoints; i++){
    outfile << setw(30) << setprecision(15) << TimePoints[i];
    outfile << setw(30) << setprecision(15) << KineticEnergy[i];
    outfile << setw(30) << setprecision(15) << PotentialEnergy[i];
    outfile << setw(30) << setprecision(15) << rEarth[i];
    outfile << setw(30) << setprecision(15) << xPos[i];
    outfile << setw(30) << setprecision(15) << yPos[i] << endl;
  }
  outfile.close();

  delete [] rEarth;
  delete [] xPos;
  delete [] yPos;
  delete [] xVel;
  delete [] yVel;
  delete [] xAcc;
  delete [] yAcc;
  delete [] TimePoints;
  delete [] KineticEnergy;
  delete [] PotentialEnergy;
  delete [] AngularMoment;

} // end of function VelocityVerlet

void odesolver::ForwardEuler(int MeshPoints, double TimeFinal){
  double TimeStep = TimeFinal/double(MeshPoints);
  double TimeStepSq = TimeStep*TimeStep;
  double TimeStepHalf = TimeStep/2;
  double TimeStepSqHalf = TimeStepSq/2;
  double FourPiSq = 4*M_PI*M_PI;
  // Arrays
  double *rEarth = new double[MeshPoints];
  double *xPos = new double[MeshPoints];
  double *yPos = new double[MeshPoints];
  double *xVel = new double[MeshPoints];
  double *yVel = new double[MeshPoints];
  double *xAcc = new double[MeshPoints];
  double *yAcc = new double[MeshPoints];
  double *TimePoints = new double[MeshPoints];
  // Initial values
  rEarth[0] = 1;
  xPos[0] = 1;
  yPos[0] = 0;
  xVel[0] = 0;
  yVel[0] = 2*M_PI;
  TimePoints[0] = 0;
  // Integration loop
  double FPSDivrEarthCu;
  for (int i = 0; i < MeshPoints; i++) {
    FPSDivrEarthCu = FourPiSq/(rEarth[i]*rEarth[i]*rEarth[i]);
    xVel[i+1] = xVel[i] - xPos[i]*TimeStep*FPSDivrEarthCu;
    xPos[i+1] = xPos[i] + TimeStep*xVel[i];
    yVel[i+1] = yVel[i] - yPos[i]*TimeStep*FPSDivrEarthCu;
    yPos[i+1] = yPos[i] + TimeStep*yVel[i];
    rEarth[i+1] = sqrt(xPos[i+1]*xPos[i+1] + yPos[i+1]*yPos[i+1]);
    TimePoints[i+1] = TimePoints[i] + TimeStep;
  }

  ofstream outfile;
  outfile.open ("EarthSunEuler.dat");
  for (int i=0; i<MeshPoints; i++){
    outfile << setw(30) << setprecision(15) << TimePoints[i];
    outfile << setw(30) << setprecision(15) << xPos[i];
    outfile << setw(30) << setprecision(15) << yPos[i] << endl;
  }
  outfile.close();

  delete [] rEarth;
  delete [] xPos;
  delete [] yPos;
  delete [] xVel;
  delete [] yVel;
  delete [] xAcc;
  delete [] yAcc;
  delete [] TimePoints;

} // end of function VelocityVerlet
