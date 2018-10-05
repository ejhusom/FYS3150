/*==============================================================================
Title:           FYS3150 Project 3
Author:          Erik Johannes B. L. G. Husom
Date:            2018-10-04
Version:         0.1
Description:
USAGE:
==============================================================================*/
#include <iostream>
#include <fstream>
#include <cmath>
#include "odesolver.h"
using namespace std;

int main(int argc, char *argv[]){
  int MeshPoints = 10000;
  double TimeFinal = 1.0;
  switch (argc) {
    case 3: TimeFinal = atof(argv[2]);
    case 2: MeshPoints = atoi(argv[1]);
  }
  odesolver EarthSun;
  EarthSun.VelocityVerlet(MeshPoints,TimeFinal);
  EarthSun.ForwardEuler(MeshPoints,TimeFinal);


  return 0;
} // end of main function
