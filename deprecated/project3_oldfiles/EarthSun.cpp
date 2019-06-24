/*==============================================================================
Title:           FYS3150 Project 3a
Author:          Erik Johannes B. L. G. Husom
Date:            2018-10-04
Version:         0.1
Description: Program for solving differential equations describing the Earth-Sun system. Info about program:
- Distance in AU
- Time in years
USAGE:
POTENTIAL IMPROVEMENTS AND NOTES:
- Use slides: http://compphysics.github.io/ComputationalPhysics/doc/pub/ode/html/ode.html
==============================================================================*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
using namespace std;

int EarthSun(int argc, char *argv[]){
  int MeshPoints = atoi(argv[1]);
  double TimeFinal = 5.0;
  double TimeStep = TimeFinal/double(MeshPoints);
  double TimeStepSq = TimeStep*TimeStep;
  double TimeStepHalf = TimeStep/2;
  // Constants
  // double GravitationalConstant = 6.674e-11;
  // double MassSun = 1.9891e30;
  // double GM_S = GravitationalConstant*MassSun;
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
  // // Euler's method
  // for (int i = 0; i < MeshPoints; i++) {
  //   xVel[i+1] = xVel[i] - xPos[i]*TimeStep*FourPiSq/(rEarth[i]*rEarth[i]*rEarth[i]);
  //   xPos[i+1] = xPos[i] + TimeStep*xVel[i];
  //   yVel[i+1] = yVel[i] - yPos[i]*TimeStep*FourPiSq/(rEarth[i]*rEarth[i]*rEarth[i]);
  //   yPos[i+1] = yPos[i] + TimeStep*yVel[i];
  //   rEarth[i+1] = sqrt(xPos[i+1]*xPos[i+1] + yPos[i+1]*yPos[i+1]);
  //   TimePoints[i+1] = TimePoints[i] + TimeStep;
  // }
  // Velocity Verlet method
  for (int i = 0; i < MeshPoints; i++) {
    xAcc[i] = -xPos[i]*FourPiSq/(rEarth[i]*rEarth[i]*rEarth[i]);
    yAcc[i] = -yPos[i]*FourPiSq/(rEarth[i]*rEarth[i]*rEarth[i]);

    xPos[i+1] = xPos[i] + TimeStep*xVel[i] + xAcc[i]*TimeStepSq/2;
    yPos[i+1] = yPos[i] + TimeStep*yVel[i] + yAcc[i]*TimeStepSq/2;
    rEarth[i+1] = sqrt(xPos[i+1]*xPos[i+1] + yPos[i+1]*yPos[i+1]);

    xAcc[i+1] = -xPos[i]*FourPiSq/(rEarth[i+1]*rEarth[i+1]*rEarth[i+1]);
    yAcc[i+1] = -yPos[i]*FourPiSq/(rEarth[i+1]*rEarth[i+1]*rEarth[i+1]);
    xVel[i+1] = xVel[i] + TimeStepHalf*(xAcc[i+1] + xAcc[i]);
    yVel[i+1] = yVel[i] + TimeStepHalf*(yAcc[i+1] + yAcc[i]);
    TimePoints[i+1] = TimePoints[i] + TimeStep;
  }
  ofstream outfile;
  outfile.open ("EarthSun.dat");
  for (int i=0; i<MeshPoints; i++){
    outfile << setw(30) << setprecision(15) << TimePoints[i];
    outfile << setw(30) << setprecision(15) << xPos[i];
    outfile << setw(30) << setprecision(15) << yPos[i] << endl;
  }
  outfile.close();


  // Arrays
  delete [] rEarth;
  delete [] xPos;
  delete [] yPos;
  delete [] xVel;
  delete [] yVel;
  delete [] xAcc;
  delete [] yAcc;
  delete [] TimePoints;

  return 0;
} // end of main function
