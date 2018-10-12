#ifndef INTEGRATOR_H
#define INTEGRATOR_H
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include "AstronomicalObject.h"
using namespace std;

class Integrator{
public:
  // Properties
  int MeshPoints;
  double TimeFinal;
  vector<AstronomicalObject> AllObjects;
  int Method;
  // Initializers
  Integrator();
  Integrator(int n, double t_f, vector<AstronomicalObject> objects, int m);
  // Functions
  void solve();

};

#endif /* INTEGRATOR_H */
