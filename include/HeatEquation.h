#ifndef HEATEQUATION_H
#define HEATEQUATION_H
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
// #include <mpi.h>
using namespace std;

class HeatEquation{
public:
  // Properties
  double Time;
  int T;
  double Lx;
  double Ly;
  double dl;
  int Nx;
  int Ny;
  double dt;
  double alpha;
  double **uNew;
  double **uOld;
  double **uGuess;
  double tolerance;
  double *Q;
  // Initializers
  HeatEquation();
  ~HeatEquation();
  // Functions
  int jacobi(int t, double **boundaryMatrix);
  void solve(double **boundaryMatrix);
  void output(ofstream &ofile);
};

#endif /* HEATEQUATION_H */
