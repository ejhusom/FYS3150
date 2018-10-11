/*==============================================================================
Title:           FYS3150 Project 3
Author:          Erik Johannes B. L. G. Husom
Date:            2018-10-04
Version:         0.1
Description:
USAGE:
- Mass given in Solar Mass
- Distance given in Astronomical Unit (AU)
==============================================================================*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include "AstronomicalObject.h"
#include "odesolver.h"
using namespace std;

int main(int argc, char *argv[]){
  int MeshPoints = 10000;
  double TimeFinal = 1.0;
  int Method = 0;
  switch (argc) {
    case 3: TimeFinal = atof(argv[2]);
    case 2: MeshPoints = atoi(argv[1]);
  }
  // FUNCTION
  // initialize(MeshPoints,TimeFinal, Method);
  // CLASS
  AstronomicalObject Sun = AstronomicalObject(1.0,0,0,0,0);
  AstronomicalObject Earth = AstronomicalObject(3.0024584e-6,1,0,0,2*M_PI);
  AstronomicalObject Jupiter = AstronomicalObject(0.0009543,50,0,0,2*M_PI);

  double TimeStep = TimeFinal/double(MeshPoints);
  double TimeStepSq = TimeStep*TimeStep;
  double TimeStepHalf = TimeStep/2;
  double TimeStepSqHalf = TimeStepSq/2;
  double FourPiSq = 4*M_PI*M_PI;
  // Arrays
  double *xPos = new double[MeshPoints];
  double *yPos = new double[MeshPoints];
  double *TimePoints = new double[MeshPoints];
  // Initial values
  xPos[0] = 1;
  yPos[0] = 0;
  TimePoints[0] = 0;
  double xAccE; double yAccE;
  // Integration loop for Earth
  for (int i = 0; i < MeshPoints; i++) {
    // Acceleration
    xAccE = Earth.acceleration(Sun,0);
    yAccE = Earth.acceleration(Sun,1);
    // Storing position
    xPos[i] = Earth.position[0];
    yPos[i] = Earth.position[1];

    Earth.position[0] = Earth.position[0] + TimeStep*Earth.velocity[0] + xAccE*TimeStepSqHalf;
    Earth.position[1] = Earth.position[1] + TimeStep*Earth.velocity[1] + yAccE*TimeStepSqHalf;

    Earth.velocity[0] = Earth.velocity[0] + TimeStepHalf*(Earth.acceleration(Sun,0) + xAccE);
    Earth.velocity[1] = Earth.velocity[1] + TimeStepHalf*(Earth.acceleration(Sun,1) + yAccE);
    TimePoints[i+1] = TimePoints[i] + TimeStep;
  }

  ofstream outfile;
  outfile.open ("ClassData.dat");
  for (int i=0; i<MeshPoints; i++){
    outfile << setw(30) << setprecision(15) << TimePoints[i];
    outfile << setw(30) << setprecision(15) << xPos[i];
    outfile << setw(30) << setprecision(15) << yPos[i] << endl;
  }
  outfile.close();

  delete [] xPos;
  delete [] yPos;
  delete [] TimePoints;

  return 0;
} // end of main function
