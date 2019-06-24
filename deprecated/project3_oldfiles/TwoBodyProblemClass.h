#ifndef TWOBODYPROBLEMCLASS_H
#define TWOBODYPROBLEMCLASS_H
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include "AstronomicalObject.h"
using namespace std;

class TwoBodyProblemClass{
public:
  // Properties
  int MeshPoints;
  double TimeFinal;
  vector<AstronomicalObject> AllObjects;
  int Method;
  // Initializers
  TwoBodyProblemClass();
  TwoBodyProblemClass(int n, double t_f, vector<AstronomicalObject> objects, int m);
  // Functions
  void solve();

};

#endif /* TWOBODYPROBLEMCLASS_H */
