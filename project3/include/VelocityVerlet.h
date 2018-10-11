#ifndef VELOCITYVERLET_H
#define VELOCITYVERLET_H
#include <fstream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "AstronomicalObject.h"
using namespace std;

class VelocityVerlet{
public:
  // Properties
  int MeshPoints;
  double TimeFinal;
  vector<AstronomicalObject> AllObjects;
  // Initializers
  VelocityVerlet();
  VelocityVerlet(int n, double t_f, vector<AstronomicalObject> objects);
  // Functions
  void solve();

};

#endif /* VELOCITYVERLET_H */
