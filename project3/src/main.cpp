/*==============================================================================
Title:           FYS3150 Project 3
Author:          Erik Johannes B. L. G. Husom
Date:            2018-10-04
Version:         0.1
Description:
- Uses classes AstronomicalObject and VelocityVerlet to simulate the solar system
- Mass given in Solar Mass
- Distance given in Astronomical Unit (AU)
USAGE:
==============================================================================*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <string>
#include "AstronomicalObject.h"
#include "VelocityVerlet.h"
#include "Integrator.h"
using namespace std;

int main(int argc, char *argv[]){
  int MeshPoints = 10000;
  double TimeFinal = 100.0;
  int Method = 0;
  switch (argc) {
    case 4: Method = atoi(argv[3]);
    case 3: TimeFinal = atof(argv[2]);
    case 2: MeshPoints = atoi(argv[1]);
  }

  // Intialize all objects
  double solarMass = 1.9891e30;
  vector<AstronomicalObject> AllObjects;
  AstronomicalObject Sun = AstronomicalObject(1.0,0,0,0,0,0,0);
  AstronomicalObject Mercury = AstronomicalObject(1.307e22/solarMass,-3.294363957786441E-01,-2.928799526088138E-01,5.618346324205380E-03,365.25*1.320405892727915E-02, 365.25*-1.952252048338632E-02, 365.25*-2.807294373094382E-03);
  AstronomicalObject Venus = AstronomicalObject(4.867E24/solarMass, 7.243545955158947E-01, -3.278712379892032E-02, -4.242728890559555E-02, 365.25*1.017391327967621E-03, 365.25* 2.010584861519629E-02, 365.25* 2.168289888508737E-04);
  AstronomicalObject Earth = AstronomicalObject(5.972E24/solarMass,9.837576984919719E-01,1.889233809711713E-01,-8.631011464030984E-05,-3.406523137555859E-03*365.25,1.686035619678342E-02*365.25,-1.194254105980157E-06*365.25);
  AstronomicalObject Mars = AstronomicalObject(6.39E23/solarMass, 1.349004548617385E+00, -2.975589233646888E-01, -3.956440841859040E-02, 365.25*3.610034965148588E-03, 365.25* 1.484808760059448E-02, 365.25* 2.224945616221949E-04);
  AstronomicalObject Jupiter = AstronomicalObject(1.898E27/solarMass,-2.724865762194714E+00,-4.624789318060123E+00,8.013249787610907E-02,6.411862928919486E-03*365.25,-3.471082490961821E-03*365.25,-1.290147901227175E-04*365.25);
  AstronomicalObject Saturn = AstronomicalObject(5.683E26/solarMass, 1.497082568921199E+00, -9.943470921581483E+00,  1.132983557425057E-01, 365.25*5.209583578051823E-03, 365.25* 8.120803848912152E-04, 365.25*-2.211308505468577E-04);
  AstronomicalObject Uranus = AstronomicalObject(8.681E25/solarMass, 1.719595695177778E+01,  9.965486713193039E+00, -1.857636424997038E-01, 365.25*-2.000761535443054E-03, 365.25* 3.219594226509228E-03, 365.25* 3.795711294500967E-05);
  AstronomicalObject Neptune = AstronomicalObject(1.024E26/solarMass, 2.891239407445751E+01, -7.753050308782163E+00, -5.066556247342422E-01, 365.25*7.926104454699854E-04, 365.25* 3.050689379330089E-03, 365.25*-8.139915196891708E-05);
  AstronomicalObject Pluto = AstronomicalObject(1.30900E22/solarMass, 1.161374129179143E+01, -3.157937303069106E+01,  1.979427629835602E-02, 365.25*3.006977217402132E-03, 365.25* 4.205759240708480E-04, 365.25*-9.057561756443009E-04);
  AllObjects.push_back(Sun);
  AllObjects.push_back(Mercury);
  AllObjects.push_back(Venus);
  AllObjects.push_back(Earth);
  AllObjects.push_back(Mars);
  AllObjects.push_back(Jupiter);
  AllObjects.push_back(Saturn);
  AllObjects.push_back(Uranus);
  AllObjects.push_back(Neptune);
  AllObjects.push_back(Pluto);

  // VelocityVerlet Solver = VelocityVerlet(MeshPoints,TimeFinal,AllObjects);
  Integrator Solver = Integrator(MeshPoints,TimeFinal,AllObjects,Method);
  Solver.solve();

  return 0;
} // end of main function
