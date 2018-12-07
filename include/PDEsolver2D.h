#ifndef PDESOLVER2D_H
#define PDESOLVER2D_H
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
// #include <mpi.h>
using namespace std;

class PDEsolver2D{
public:
  // Properties
  string methodName;
  int N;
  double Time;
  int T;
  double dt;
  double dx;
  double alpha;
  double method;
  double **uNew;
  double **uOld;
  double **uGuess;
  double tolerance;
  // Initializers
  PDEsolver2D();
  PDEsolver2D(int N_, double dt_, double T_, double method_);
  ~PDEsolver2D();
  // Functions
  int jacobi();
  void solve();
  void output(ofstream &ofile);
};

#endif /* PDESOLVER2D_H */
