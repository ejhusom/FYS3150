#ifndef HEATEQUATION_H
#define HEATEQUATION_H
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <armadillo>
// #include <mpi.h>
using namespace std;
using namespace arma;

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
  double beta;
  double gamma;
  double **uNew;
  double **uOld;
  double **uGuess;
  double tolerance;
  double *Q;
  double *Q4;
  int slab;
  int radioactive;
  // Initializers
  HeatEquation(int _slab, int _radioactive);
  ~HeatEquation();
  // Functions
  int jacobi(int t, double **boundaryMatrix);
  void solve(double **boundaryMatrix);
  void output(ofstream &ofile);
  void decay(double l, double k);
};

#endif /* HEATEQUATION_H */
