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
#include <vector>
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
  vector<AstronomicalObject> AllObjects;
  AstronomicalObject Sun = AstronomicalObject(1.0,0,0,0,0,0,0);
  AstronomicalObject Earth = AstronomicalObject(3.0024584e-6,9.837576984919719E-01,1.889233809711713E-01,-8.631011464030984E-05,-3.406523137555859E-03*365.25,1.686035619678342E-02*365.25,-1.194254105980157E-06*365.25);
  AstronomicalObject Jupiter = AstronomicalObject(0.0009543,-2.724865762194714E+00,-4.624789318060123E+00,8.013249787610907E-02,6.411862928919486E-03*365.25,-3.471082490961821E-03*365.25,-1.290147901227175E-04*365.25);
  AllObjects.push_back(Sun);
  AllObjects.push_back(Earth);
  AllObjects.push_back(Jupiter);
  // Pre-calculations
  double TimeStep = TimeFinal/double(MeshPoints);
  double TimeStepSq = TimeStep*TimeStep;
  double TimeStepHalf = TimeStep/2;
  double TimeStepSqHalf = TimeStepSq/2;
  // Arrays
  double *xPos = new double[MeshPoints];
  double *yPos = new double[MeshPoints];
  double *zPos = new double[MeshPoints];
  // Temporary acceleration values
  double xAcc; double yAcc; double xAccNew; double yAccNew; double zAcc; double zAccNew;
  // Open file for writing
  ofstream outfile;
  outfile.open ("ClassData33.dat");
  // Integration loop for Earth
  for (int i = 0; i < MeshPoints; i++) {
    for (int obj = 0; obj < AllObjects.size(); obj++) {
      xAcc = yAcc = xAccNew = yAccNew = zAcc = zAccNew = 0;
      // Acceleration
      for (int obj2 = 0; obj2 < AllObjects.size(); obj2++){
        xAcc += AllObjects[obj].acceleration(AllObjects[obj2],0);
        yAcc += AllObjects[obj].acceleration(AllObjects[obj2],1);
        zAcc += AllObjects[obj].acceleration(AllObjects[obj2],2);
      }
      // Storing position
      outfile << setw(30) << setprecision(15) << AllObjects[obj].position[0];
      outfile << setw(30) << setprecision(15) << AllObjects[obj].position[1];
      outfile << setw(30) << setprecision(15) << AllObjects[obj].position[2];

      AllObjects[obj].position[0] = AllObjects[obj].position[0] + TimeStep*AllObjects[obj].velocity[0] + xAcc*TimeStepSqHalf;
      AllObjects[obj].position[1] = AllObjects[obj].position[1] + TimeStep*AllObjects[obj].velocity[1] + yAcc*TimeStepSqHalf;
      AllObjects[obj].position[2] = AllObjects[obj].position[2] + TimeStep*AllObjects[obj].velocity[2] + zAcc*TimeStepSqHalf;

      for (int obj2 = 0; obj2 < AllObjects.size(); obj2++){
        xAccNew += AllObjects[obj].acceleration(AllObjects[obj2],0);
        yAccNew += AllObjects[obj].acceleration(AllObjects[obj2],1);
        zAccNew += AllObjects[obj].acceleration(AllObjects[obj2],2);
      }

      AllObjects[obj].velocity[0] = AllObjects[obj].velocity[0] + TimeStepHalf*(xAccNew + xAcc);
      AllObjects[obj].velocity[1] = AllObjects[obj].velocity[1] + TimeStepHalf*(yAccNew + yAcc);
      AllObjects[obj].velocity[2] = AllObjects[obj].velocity[2] + TimeStepHalf*(zAccNew + zAcc);
    }
    outfile << endl;
  }


  outfile.close();

  delete [] xPos;
  delete [] yPos;
  delete [] zPos;

  return 0;
} // end of main function
