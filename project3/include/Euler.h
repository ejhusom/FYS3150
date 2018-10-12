#ifndef EULER_H
#define EULER_H
#include <fstream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "AstronomicalObject.h"
using namespace std;

class Euler{
public:
  // Properties
  int MeshPoints;
  double TimeFinal;
  vector<AstronomicalObject> AllObjects;
  // Initializers
  Euler();
  Euler(int n, double t_f, vector<AstronomicalObject> objects);
  // Functions
  void solve();

};

#endif /* EULER_H */
