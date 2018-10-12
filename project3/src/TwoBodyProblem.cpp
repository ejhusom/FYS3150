#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
#include "TwoBodyProblem.h"

using namespace std;

void initialize(int MeshPoints, double TimeFinal, int Method){
  double EarthMass = 0.000003003; // in solar mass
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
  double FPSDivrEarthCu;
  string filename;
  // Integration loop
  if (Method == 0) {
    filename = "TwoBodyProblemVerlet.dat";
    for (int i = 0; i < MeshPoints; i++) {
      FPSDivrEarthCu = FourPiSq/(rEarth[i]*rEarth[i]*rEarth[i]);
      xAcc[i] = -xPos[i]*FPSDivrEarthCu;
      yAcc[i] = -yPos[i]*FPSDivrEarthCu;

      xPos[i+1] = xPos[i] + TimeStep*xVel[i] + xAcc[i]*TimeStepSqHalf;
      yPos[i+1] = yPos[i] + TimeStep*yVel[i] + yAcc[i]*TimeStepSqHalf;

      rEarth[i+1] = sqrt(xPos[i+1]*xPos[i+1] + yPos[i+1]*yPos[i+1]);
      FPSDivrEarthCu = FourPiSq/(rEarth[i+1]*rEarth[i+1]*rEarth[i+1]);

      xAcc[i+1] = -xPos[i+1]*FPSDivrEarthCu;
      yAcc[i+1] = -yPos[i+1]*FPSDivrEarthCu;
      xVel[i+1] = xVel[i] + TimeStepHalf*(xAcc[i+1] + xAcc[i]);
      yVel[i+1] = yVel[i] + TimeStepHalf*(yAcc[i+1] + yAcc[i]);
    }
  } else {
    filename = "TwoBodyProblemEuler.dat";
    for (int i = 0; i < MeshPoints; i++) {
      FPSDivrEarthCu = FourPiSq/(rEarth[i]*rEarth[i]*rEarth[i]);
      xVel[i+1] = xVel[i] - xPos[i]*TimeStep*FPSDivrEarthCu;
      xPos[i+1] = xPos[i] + TimeStep*xVel[i];
      yVel[i+1] = yVel[i] - yPos[i]*TimeStep*FPSDivrEarthCu;
      yPos[i+1] = yPos[i] + TimeStep*yVel[i];
      rEarth[i+1] = sqrt(xPos[i+1]*xPos[i+1] + yPos[i+1]*yPos[i+1]);
    }
  }
  for (int i = 0; i < MeshPoints; i++) {
    KineticEnergy[i] = 0.5*EarthMass*(xVel[i]*xVel[i] + yVel[i]*yVel[i]);
    PotentialEnergy[i] = -4*M_PI*M_PI*EarthMass/rEarth[i];
    AngularMoment[i] = xPos[i]*yVel[i] - yPos[i]*xVel[i];
    TimePoints[i+1] = TimePoints[i] + TimeStep;
  }

  ofstream outfile;
  outfile.open (filename);
  for (int i=0; i<MeshPoints; i++){
    outfile << setw(30) << setprecision(15) << TimePoints[i];
    outfile << setw(30) << setprecision(15) << KineticEnergy[i];
    outfile << setw(30) << setprecision(15) << PotentialEnergy[i];
    outfile << setw(30) << setprecision(15) << AngularMoment[i];
    outfile << setw(30) << setprecision(15) << rEarth[i];
    outfile << setw(30) << setprecision(15) << xPos[i];
    outfile << setw(30) << setprecision(15) << yPos[i] << endl;
  }
  outfile.close();

  // TEST No. 1: Checking conservation of kinetic energy
  struct winsize size;
  ioctl(STDOUT_FILENO,TIOCGWINSZ,&size);
  for (int i = 0; i < size.ws_col; i++) {
    cout << "=";
  }
  cout << endl;
  if (Method == 0) cout << "Method: Velociy Verlet\n";
  else cout << "Method: Euler\n";
  double tolerance = 1e-6;
  double success = true;
  cout << left << setw(35) << "TEST: Conserved kinetic energy, " << setw(10) << "tol=1e-6";
  for (int i=0; i<MeshPoints; i++){
    if (fabs(KineticEnergy[0]-KineticEnergy[i]) > tolerance){
      cout << left << " | \033[1;31mFAILED\033[0m" << endl;
      success = false;
      break;
    }
  }
  if (success){
    cout << left << " | \033[1;32mPASSED\033[0m" << endl;
  }

  // TEST No. 2: Checking conservation of potential energy
  tolerance = 1e-6;
  success = true;
  cout << left << setw(35) << "TEST: Conserved potential energy, " << setw(10) << "tol=1e-6";
  for (int i=0; i<MeshPoints; i++){
    if (fabs(PotentialEnergy[0]-PotentialEnergy[i]) > tolerance){
      cout << left << " | \033[1;31mFAILED\033[0m" << endl;
      success = false;
      break;
    }
  }
  if (success){
    cout << left << " | \033[1;32mPASSED\033[0m" << endl;
  }

  // TEST No. 3: Checking conservation of angular moment
  tolerance = 1e-10;
  success = true;
  cout << left << setw(35) << "TEST: Conserved angular moment, " << setw(10) << "tol=1e-10";
  for (int i=0; i<MeshPoints; i++){
    if (fabs(AngularMoment[0]-AngularMoment[i]) > tolerance){
      cout << left << " | \033[1;31mFAILED\033[0m" << endl;
      success = false;
      break;
    }
  }
  if (success){
    cout << left << " | \033[1;32mPASSED\033[0m" << endl;
  }

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

}
